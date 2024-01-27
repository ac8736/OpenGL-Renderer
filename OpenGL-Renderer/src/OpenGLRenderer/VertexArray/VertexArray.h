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

		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const;

		void AddVertexBuffer(std::shared_ptr<OpenGLRenderer::VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer);
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<OpenGLRenderer::VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}
