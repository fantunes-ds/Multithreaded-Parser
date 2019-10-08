#include <memory>
#include <iostream>

#include <Core/GameObject.h>
#include <Core/Components/ModelComponent.h>

#include <Rendering/LowRenderer/Camera.h>
#include <Rendering/LowRenderer/Light.h>

using namespace Core;

std::vector<std::shared_ptr<Components::IComponent>>& GameObject::GetComponents() { return m_components; }

GameObject::GameObject(const GameObject & p_other)
{
	std::cout << "used GameObject copy constructor\n";
	m_components = p_other.m_components;
	m_transform = p_other.m_transform;
}

void Core::GameObject::MoveTo(glm::vec3 & p_vec)
{
	m_transform.SetPos(p_vec);
}

void Core::GameObject::TranslateBy(glm::vec3 & p_vec)
{
	glm::vec3 newPos = m_transform.GetPos() + p_vec;
	m_transform.SetPos(newPos);
}

void Core::GameObject::SetTransform(glm::vec3 & p_pos, glm::vec3 & p_rot, glm::vec3 & p_scale)
{
	m_transform.SetTransform(p_pos, p_rot, p_scale);
}

void Core::GameObject::SetTransform(Rendering::Resources::Transform& p_transform)
{
	m_transform = p_transform;
}

void GameObject::AddTexture(const std::string& p_texturePath) const
{
	if (GetComponent<Core::Components::ModelComponent>() == nullptr)
		return;

	Rendering::Resources::Model& model = *GetComponent<Core::Components::ModelComponent>()->GetModel();
	model.AddTexture(p_texturePath);
}

void Core::GameObject::UpdateAllComponents()
{
	for (auto& component : m_components)
		component->Update();
}

void Core::GameObject::UpdateShaders()
{
	if (GetComponent<Core::Components::ModelComponent>() == nullptr || GetComponent<Core::Components::ModelComponent>()->GetMesh() == nullptr || m_isInitialized)
		return;

	glm::mat4 projection = Rendering::LowRenderer::Camera::GetInstance()->GetProjectionMatrix();
	glm::mat4 view = Rendering::LowRenderer::Camera::GetInstance()->GetViewMatrix();

	Rendering::Resources::Model& model = *GetComponent<Core::Components::ModelComponent>()->GetModel();
	Rendering::Resources::Shader& shader = *model.GetShader();

	glm::mat4 modelMatrix = m_transform.GetModelMatrix();

	glm::vec3 cameraPos = Rendering::LowRenderer::Camera::GetInstance()->GetPos();

	struct Rendering::LowRenderer::LightSource lights;
	lights.Position = glm::vec3(0.0f, 0.0f, 0.0f);
	lights.Ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	lights.Diffuse = glm::vec3(1.0f, 1.0f, 0.95f);
	lights.Direction = glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f));
	lights.Specular = glm::vec3(1.0f, 1.0f, 0.95f);

	shader.Bind();
	shader.SetUniformMatrix4fv("modelMatrix", modelMatrix);
	shader.SetUniformMatrix4fv("projectionMatrix", projection);
	shader.SetUniformMatrix4fv("viewMatrix", view);
	shader.SetUniform3f("ViewPos", cameraPos.x, cameraPos.y, cameraPos.z);
	//shader.SetUniform3f("lightSource.Position", lights.Position.x, lights.Position.y, lights.Position.z);
	shader.SetUniform3f("lightSource.Diffuse", lights.Diffuse.x, lights.Diffuse.y, lights.Diffuse.z);
	shader.SetUniform3f("lightSource.Direction", lights.Direction.x, lights.Direction.y, lights.Direction.z);
	shader.SetUniform3f("lightSource.Specular", lights.Specular.x, lights.Specular.y, lights.Specular.z);
	if (model.GetTexture()->IsTextureSet() != NULL)
	{
		shader.SetBool("useTexture", true);
		shader.SetInt("objectTexture", 1);
	}
	else
	{
		shader.SetBool("useTexture", false);
	}
	shader.Unbind();
	m_isInitialized = true;

}

void GameObject::RecompileShaders() const
{
	if (GetComponent<Core::Components::ModelComponent>() == nullptr)
		return;

	Rendering::Resources::Shader& shader = *GetComponent<Core::Components::ModelComponent>()->GetModel()->GetShader();
	shader.RecompileShader();
}
