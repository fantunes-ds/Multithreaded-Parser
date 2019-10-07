#include <stdafx.h>

#include <Rendering/Resources/Model.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <thread>
#include <Rendering/Resources/ResourceManager.h>


Rendering::Resources::Model::Model(const std::string& p_path) noexcept
{
	LoadModel(p_path);
	LoadShader();
}

Rendering::Resources::Model::Model(const std::string& p_modelPath,
	const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	LoadModel(p_modelPath);
	LoadShader(p_vertexFilepath, p_fragmentFilepath);
}

Rendering::Resources::Model::Model(const Model& p_other) noexcept
{
	m_directory = p_other.m_directory;
	m_mesh = p_other.m_mesh;
	m_shader = p_other.m_shader;
	m_meshPath = p_other.m_meshPath;
}

void Rendering::Resources::Model::AddTexture(const std::string& p_texturePath) const
{
	m_mesh->AddTexture(p_texturePath);
}

void Rendering::Resources::Model::LoadModel(const std::string& p_path) noexcept
{
	m_meshPath = p_path;
	std::unordered_map<std::string, std::shared_ptr<Mesh>>& meshMap = ResourceManager::GetInstance()->GetMeshMap();
	std::unordered_map<std::string, ResourceManager::meshStatus>& meshMapQueue = ResourceManager::GetInstance()->GetMeshMapQueue();
	if (meshMap.find(p_path) == meshMap.cend() && meshMapQueue.find(p_path) == meshMapQueue.cend())
	{
		meshMapQueue.insert_or_assign(p_path, ResourceManager::meshStatus::LOADING);
		//ResourceManager::GetInstance()->AddMesh(p_path); 
		std::thread t1 { &ResourceManager::AddMesh, ResourceManager::GetInstance().get(), p_path };
	    t1.detach();
	}
	else if (meshMapQueue.find(p_path)->second == ResourceManager::meshStatus::LOADED)
	{
		m_mesh = meshMap.find(p_path)->second;
		m_mesh->CreateBuffers();
	}
}

void Rendering::Resources::Model::RetryLoadModel() noexcept
{
    if(!m_meshPath.empty())
	LoadModel(m_meshPath);
}

void Rendering::Resources::Model::LoadShader(const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	m_shader = std::make_shared<Shader>(*Loaders::ShaderLoader::Load(p_vertexFilepath, p_fragmentFilepath));
}

void Rendering::Resources::Model::Bind() const noexcept
{
	m_mesh->Bind();
	m_shader->Bind();
}

void Rendering::Resources::Model::Unbind() const noexcept
{
	m_mesh->Unbind();
	m_shader->Unbind();
}
