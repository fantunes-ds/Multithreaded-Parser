#include <stdafx.h>

#include <thread>

#include <Rendering/Resources/Model.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/Managers/ResourceManager.h>

Rendering::Resources::Model::Model(const std::string& p_path) noexcept
{
	LoadModel(p_path);
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

	std::unordered_map<std::string, std::pair<std::shared_ptr<Mesh>, Managers::ResourceManager::meshStatus>>& meshMapState = Managers::ResourceManager::GetInstance()->GetMeshMap();
	if (meshMapState.find(p_path) == meshMapState.cend())
	{
		meshMapState.insert_or_assign(p_path, std::make_pair(nullptr, Managers::ResourceManager::meshStatus::LOADING));
		//ResourceManager::GetInstance()->AddMesh(p_path); 
		std::thread t1 { &Managers::ResourceManager::AddMesh, Managers::ResourceManager::GetInstance().get(), p_path };
	    t1.detach(); 
	}
	else if (meshMapState.find(p_path)->second.second == Managers::ResourceManager::meshStatus::LOADED)
	{
		m_mesh = meshMapState.find(p_path)->second.first;
		m_mesh->CreateBuffers();
		LoadShader();
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
