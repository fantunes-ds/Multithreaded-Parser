#include <stdafx.h>
#include <Rendering/Resources/Mesh.h>

Rendering::Resources::Mesh::Mesh(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices) noexcept
	: m_vertexCount{ static_cast<uint32_t>(p_vertices.size()) }, m_indicesCount{ static_cast<uint32_t>(p_indices.size()) }, m_vertices{ p_vertices }, m_indices{ p_indices }
{
	m_texture = std::make_shared<Texture>();	
}

void Rendering::Resources::Mesh::AddTexture(const std::string& p_texturePath)
{
	m_texture->Load(p_texturePath);
}

void Rendering::Resources::Mesh::Bind() const noexcept
{
	m_texture->Bind();
	m_vertexArray->Bind();
	m_indexBuffer->Bind();
}

void Rendering::Resources::Mesh::Unbind() const noexcept
{
	m_indexBuffer->Unbind();
	m_vertexArray->Unbind();
	m_texture->Unbind();
}

const uint32_t Rendering::Resources::Mesh::GetVertexCount() const noexcept
{
	return m_vertexCount;
}

const uint32_t Rendering::Resources::Mesh::GetIndicesCount() const noexcept
{
	return m_indicesCount;
}

void Rendering::Resources::Mesh::CreateBuffers() noexcept
{
	m_isBuffersGenerated = true;
	m_vertexArray = std::make_unique<Buffers::VertexArray>();

	m_vertexArray->Bind();

	std::vector<float> rawPositions{};
	std::vector<float> rawTextCoords{};
	std::vector<float> rawNormals{};

	for (const auto& vertex: m_vertices)
	{
		// Position
		rawPositions.push_back(vertex.m_position[0]);
		rawPositions.push_back(vertex.m_position[1]);
		rawPositions.push_back(vertex.m_position[2]);

		// TextCoord
		rawTextCoords.push_back(vertex.m_textCoords[0]);
		rawTextCoords.push_back(vertex.m_textCoords[1]);

		// Normal
		rawNormals.push_back(vertex.m_normal[0]);
		rawNormals.push_back(vertex.m_normal[1]);
		rawNormals.push_back(vertex.m_normal[2]);
	}

	// Buffer gen
	m_vboPosition = std::make_unique<Buffers::VertexBuffer>(rawPositions);
	m_vboTextCoords = std::make_unique<Buffers::VertexBuffer>(rawTextCoords);
	m_vboNormal = std::make_unique<Buffers::VertexBuffer>(rawNormals);

	m_indexBuffer = std::make_unique<Buffers::IndexBuffer>(m_indices);

	m_vertexArray->AddBuffer(*m_vboPosition, 3, Buffers::GLType::FLOAT);
	m_vertexArray->AddBuffer(*m_vboTextCoords, 2, Buffers::GLType::FLOAT);
	m_vertexArray->AddBuffer(*m_vboNormal, 3, Buffers::GLType::FLOAT);

    m_vertexArray->Unbind();

}
