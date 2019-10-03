#include <stdafx.h>

#include <Rendering/Resources/Model.h>
#include <Rendering/Geometry/Vertex.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Rendering/Resources/ParserOBJ.h>
#include <chrono>
#include <thread>


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

	std::deque<glm::vec3> rawVertPos{};
	std::deque<glm::vec2> rawUVs{};
	std::deque<glm::vec3> rawNormals{};

	std::deque<uint32_t> rawIndices{};
	std::deque<uint32_t> rawVertexIndices{};
    std::deque<uint32_t> rawUVIndices{};
    std::deque<uint32_t> rawNormalIndices{};
#pragma endregion

    std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
    
    //ParserOBJ::ReadAndStoreRawData(p_path.c_str(), rawVertPos, rawUVs, rawNormals, rawIndices);
	std::thread t1 { &ParserOBJ::ReadAndStoreRawData, p_path.c_str(), std::ref(rawVertPos), std::ref(rawUVs), std::ref(rawNormals), std::ref(rawIndices) };
	t1.join();

	//ParserOBJ::ArrangeIndices(rawIndices, rawVertexIndices, rawUVIndices, rawNormalIndices);
	std::thread t2 {&ParserOBJ::ArrangeIndices, std::ref(rawIndices), std::ref(rawVertexIndices), std::ref(rawUVIndices), std::ref(rawNormalIndices)};
	t2.join();
       
    for (unsigned int i = 0; i < rawVertexIndices.size(); i++)
	{
		Geometry::Vertex tempvert{ rawVertPos[rawVertexIndices[i] - 1], rawUVs[rawUVIndices[i] - 1], rawNormals[rawNormalIndices[i] - 1] };
		vertices.push_back(tempvert);
	}

	std::vector<uint32_t> fakePosIndices;
	for (unsigned int i = 0; i < rawIndices.size(); i++)
		fakePosIndices.push_back(i);

	end = std::chrono::system_clock::now();
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Done loading one object in " << elapsed_seconds << " millisec" << '\n';

    m_mesh = std::make_shared<Mesh>(vertices, fakePosIndices);


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
