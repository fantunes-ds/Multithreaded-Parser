#include <stdafx.h>

#include <Rendering/Resources/Model.h>
#include <Rendering/Geometry/Vertex.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Rendering/Resources/ParserOBJ.h>


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
}

void Rendering::Resources::Model::AddTexture(const std::string& p_texturePath) const
{
	m_mesh->AddTexture(p_texturePath);
}

void Rendering::Resources::Model::LoadModel(const std::string& p_path) noexcept
{
#pragma region VarDeclarations
    std::vector<Geometry::Vertex> vertices;

	std::vector<glm::vec3> rawVertPos{};
	std::vector<glm::vec2> rawUVs{};
	std::vector<glm::vec3> rawNormals{};
	std::vector<uint32_t> rawIndices{};
	std::vector<uint32_t> rawVertexIndices;
    std::vector<uint32_t> rawUVIndices;
    std::vector<uint32_t> rawNormalIndices;
#pragma endregion

	ParserOBJ::ReadAndStoreRawData(p_path, rawVertPos, rawUVs, rawNormals, rawIndices);

	ParserOBJ::ArrangeIndices(rawIndices, rawVertexIndices, rawUVIndices, rawNormalIndices);

    for (unsigned int i = 0; i < rawVertexIndices.size(); i++)
	{
		Geometry::Vertex tempvert{ rawVertPos[rawVertexIndices[i] - 1], rawUVs[rawUVIndices[i] - 1], rawNormals[rawNormalIndices[i] - 1] };
		vertices.push_back(tempvert);
	}

	std::vector<uint32_t> fakePosIndices;
	for (unsigned int i = 0; i < rawIndices.size(); i++)
		fakePosIndices.push_back(i);

    m_mesh = std::make_shared<Mesh>(vertices, fakePosIndices);
}

void Rendering::Resources::Model::LoadShader(const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	m_shader = std::make_shared<Shader>(*Loaders::ShaderLoader::
		Load(p_vertexFilepath, p_fragmentFilepath));
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
