#pragma once

#include <vector>

#include <Rendering/Export.h>

#include <Rendering/Buffers/VertexBuffer.h>
#include <Rendering/Buffers/VertexArray.h>
#include <Rendering/Buffers/IndexBuffer.h>

#include <Rendering/Geometry/Vertex.h>

#include <Rendering/Resources/Shader.h>
#include <Rendering/Resources/Texture.h>

namespace Rendering::Resources
{
	class API_RENDERING Mesh
	{
	public:
		Mesh() = default;
		Mesh(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices) noexcept;
		~Mesh() noexcept = default;

		void AddTexture(const std::string & p_texturePath);

		void Bind() const noexcept;
		void Unbind() const noexcept;

		const uint32_t GetVertexCount() const noexcept;
		const uint32_t GetIndicesCount() const noexcept;

		std::shared_ptr<Texture>& GetTexture() { return m_texture; };

		void CreateBuffers(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices) noexcept;

	private:
		const uint32_t m_vertexCount{};
		const uint32_t m_indicesCount{};

		std::unique_ptr<Buffers::VertexArray> m_vertexArray;
		std::unique_ptr<Buffers::VertexBuffer> m_vboPosition;
		std::unique_ptr<Buffers::VertexBuffer> m_vboTextCoords;
		std::unique_ptr<Buffers::VertexBuffer> m_vboNormal;
		std::unique_ptr<Buffers::IndexBuffer> m_indexBuffer;
		std::shared_ptr<Texture> m_texture;
	};
}
