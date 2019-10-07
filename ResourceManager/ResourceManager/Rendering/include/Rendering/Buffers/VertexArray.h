#pragma once

#include <GL/glew.h>

#include <Rendering/Export.h>
#include <Rendering/Buffers/VertexBuffer.h>

namespace Rendering::Buffers
{
	enum class GLType
	{
		FLOAT = GL_FLOAT,
		DOUBLE = GL_DOUBLE,
		INT = GL_INT,
	};

	class API_RENDERING VertexArray // VAO
	{
	public:
		VertexArray() noexcept;
		~VertexArray() noexcept;

		void Bind() const noexcept;
		void Unbind() const noexcept;

		[[nodiscard]] const GLuint& GetId() const noexcept;
		void AddBuffer(const VertexBuffer& p_buffer, const size_t& p_countElements, const GLType& p_type) noexcept;

	private:
		GLuint m_id{};
		uint8_t m_availableLocation{ 0u };
	};
}