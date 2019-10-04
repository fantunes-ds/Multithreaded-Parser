#include <stdafx.h>

#include <chrono>
#include <thread>

#include <Rendering/Resources/ResourceManager.h>
#include <Rendering/Resources/ParserOBJ.h>

std::unique_ptr<Rendering::Resources::ResourceManager> Rendering::Resources::ResourceManager::m_instance;

void Rendering::Resources::ResourceManager::AddMesh(const std::string& p_path)
{
#pragma region VarDeclarations
	std::vector<Geometry::Vertex> vertices;

	std::vector<glm::vec3> rawVertPos{};
	std::vector<glm::vec2> rawUVs{};
	std::vector<glm::vec3> rawNormals{};

    std::vector<uint32_t> rawIndices{};
	std::vector<uint32_t> rawVertexIndices{};
	std::vector<uint32_t> rawUVIndices{};
	std::vector<uint32_t> rawNormalIndices{};
#pragma endregion

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	//ParserOBJ::ReadAndStoreRawData(p_path.c_str(), rawVertPos, rawUVs, rawNormals, rawIndices);
	std::thread t1{ &ParserOBJ::ReadAndStoreRawData, p_path.c_str(), std::ref(rawVertPos), std::ref(rawUVs), std::ref(rawNormals), std::ref(rawIndices) };
	t1.join();

	//ParserOBJ::ArrangeIndices(rawIndices, rawVertexIndices, rawUVIndices, rawNormalIndices);
	std::thread t2{ &ParserOBJ::ArrangeIndices, std::ref(rawIndices), std::ref(rawVertexIndices), std::ref(rawUVIndices), std::ref(rawNormalIndices) };
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

	m_meshMap.insert_or_assign(p_path, std::make_shared<Mesh>(vertices, fakePosIndices));
    //m_meshes.emplace_back(std::make_shared<Mesh>(vertices, fakePosIndices));
}

std::unique_ptr<Rendering::Resources::ResourceManager>& Rendering::Resources::ResourceManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::make_unique<ResourceManager>();
	}
	assert(m_instance != nullptr);
	return m_instance;
}

void Rendering::Resources::ResourceManager::RemoveMesh()
{
}
