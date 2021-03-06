#include <stdafx.h>

#include <chrono>
#include <thread>

#include <Rendering/Managers/ResourceManager.h>
#include <Rendering/Resources/ParserOBJ.h>

#define MULTITHREADING 1 // 0 -> off | 1 -> on

std::unique_ptr<Rendering::Managers::ResourceManager> Rendering::Managers::ResourceManager::m_instance;

void Rendering::Managers::ResourceManager::AddMesh(const std::string& p_path)
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
#if (MULTITHREADING == 0)
    Resources::ParserOBJ::ReadAndStoreRawData(p_path.c_str(), rawVertPos, rawUVs, rawNormals, rawIndices);
#elif (MULTITHREADING == 1)
    std::thread t1{ &Resources::ParserOBJ::ReadAndStoreRawData, p_path.c_str(), std::ref(rawVertPos), std::ref(rawUVs), std::ref(rawNormals), std::ref(rawIndices) };
	t1.join();
#endif
#if (MULTITHREADING == 0)
    Resources::ParserOBJ::ArrangeIndices(rawIndices, rawVertexIndices, rawUVIndices, rawNormalIndices);
#elif (MULTITHREADING == 1)
    std::thread t2{ &Resources::ParserOBJ::ArrangeIndices, std::ref(rawIndices), std::ref(rawVertexIndices), std::ref(rawUVIndices), std::ref(rawNormalIndices) };
	t2.join();
#endif
	for (unsigned int i = 0; i < rawVertexIndices.size(); i++)
	{
        Geometry::Vertex tempvert{ rawVertPos[rawVertexIndices[i] - 1], rawUVs[rawUVIndices[i] - 1], rawNormals[rawNormalIndices[i] - 1] };
		vertices.push_back(tempvert);
	}

	std::vector<uint32_t> fakePosIndices;
	for (unsigned int i = 0; i < rawIndices.size(); i++)
		fakePosIndices.push_back(i);

	end = std::chrono::system_clock::now();
	auto elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Done loading one object in " << elapsed_seconds << " millisec" << '\n';

	m_meshMap.insert_or_assign(p_path, std::make_pair(std::make_shared<Resources::Mesh>(vertices, fakePosIndices), meshStatus::LOADED));
}

std::unique_ptr<Rendering::Managers::ResourceManager>& Rendering::Managers::ResourceManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::make_unique<ResourceManager>();
	}
	assert(m_instance != nullptr);
	return m_instance;
}