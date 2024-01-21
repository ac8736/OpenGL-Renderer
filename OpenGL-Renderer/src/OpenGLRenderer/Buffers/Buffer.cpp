#include "glpch.h"
#include "Buffer.h"

namespace OpenGLRenderer
{
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		m_Stride = 0;
		uint32_t offset = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			m_Stride += element.Size;
			offset += element.Size;
		}
	}

	VertexBuffer::VertexBuffer(const float* vertices, unsigned int arrayLength)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, arrayLength * sizeof(float), vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// ----------------------------- //

	IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int arrayLength) 
		: m_Count(arrayLength)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, arrayLength * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
