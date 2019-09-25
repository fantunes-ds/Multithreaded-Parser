#include <stdafx.h>
#include <Rendering/Buffers/VertexBuffer.h>

using namespace Rendering::Buffers;


VertexBuffer::VertexBuffer(const float* p_data, const size_t& p_countData) noexcept
{
	glGenBuffers(1, &m_id);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, p_countData * sizeof(float), p_data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const std::vector<float>& p_data) noexcept
	: VertexBuffer{ p_data.data(), p_data.size() }
{
}

VertexBuffer::~VertexBuffer() noexcept
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::Bind() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::LoadData(const void* p_data, const GLsizeiptr& p_sizeData) noexcept
{
	glBufferData(GL_ARRAY_BUFFER, p_sizeData, p_data, GL_STATIC_DRAW);
}
