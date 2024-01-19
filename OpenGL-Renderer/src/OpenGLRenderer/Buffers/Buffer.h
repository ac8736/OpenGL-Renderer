#pragma once

#include <glad/glad.h>

namespace OpenGLRenderer
{
	struct BufferLayout
	{

	};

	// ---------------------------------------------- //

	class VertexBuffer
	{
	public:
		VertexBuffer(const float* vertices, unsigned int arrayLength);
		~VertexBuffer();

		void Bind();
		void Unbind();

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; };
	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	// --------------------------------------------- //

	class IndexBuffer
	{
	public:
		IndexBuffer(const unsigned int* indices, unsigned int arrayLength);
		~IndexBuffer();

		void Bind();
		void Unbind();
	private:
		unsigned int m_RendererID;
	};
}