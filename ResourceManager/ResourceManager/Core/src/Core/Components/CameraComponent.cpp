#include <Core/GameObject.h>
#include <Core/Components/CameraComponent.h>

using namespace Core::Components;

CameraComponent::CameraComponent(Core::GameObject& p_gameObject, glm::vec3& p_distanceFromPlayer) :
	m_gameObject { p_gameObject }, m_distanceFromPlayer { p_distanceFromPlayer }
{
	glm::vec3 newPos = Rendering::LowRenderer::Camera::GetInstance()->GetPos() + m_distanceFromPlayer;
	Rendering::LowRenderer::Camera::GetInstance()->SetPos(newPos);

	glm::vec3 newRot = Rendering::LowRenderer::Camera::GetInstance()->GetForward();
}

const std::string Core::Components::CameraComponent::GetType() const
{
	return { "CameraComponent" };
}

void Core::Components::CameraComponent::Update()
{
	Rendering::LowRenderer::Camera::GetInstance()->GetViewMatrix();
}


