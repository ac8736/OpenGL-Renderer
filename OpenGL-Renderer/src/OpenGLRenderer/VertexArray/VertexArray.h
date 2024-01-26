#pragma once

#include "OpenGLRenderer/Buffers/Buffer.h"
#include "OpenGLRenderer/Core.h"

namespace OpenGLRenderer
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		const IndexBuffer& GetIndexBuffer() const;

		void AddVertexBuffer(std::shared_ptr<OpenGLRenderer::VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const IndexBuffer& indexBuffer);
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<OpenGLRenderer::VertexBuffer>> m_VertexBuffers;
		IndexBuffer m_IndexBuffer;
	};
}
