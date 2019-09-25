#pragma once
#include <vector>
#include <GL/glew.h>
#include <Rendering/Export.h>

namespace Rendering::Buffers
{
	class API_RENDERING IndexBuffer // EBO
	{
	public:
		IndexBuffer() = delete;
		IndexBuffer(const uint32_t* p_data, const size_t& p_countData) noexcept;
		explicit IndexBuffer(const std::vector<uint32_t>& p_data) noexcept;
		~IndexBuffer() noexcept;

		void Bind() const noexcept;
		void Unbind() const noexcept;
		void LoadData(const void* p_data, const GLsizeiptr& p_sizeData) noexcept;

	private:
		GLuint m_id{};
	};

}