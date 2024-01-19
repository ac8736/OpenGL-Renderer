#include "glpch.h"
#include "VertexArray.h"

namespace OpenGLRenderer
{
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    const std::shared_ptr<IndexBuffer> VertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }

    void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        auto& layout = vertexBuffer->GetLayout();
        unsigned int index = 0;
        for (auto& vertex : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, vertex.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(vertex.Type), 
                                  vertex.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)vertex.Offset);
            ++index;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}
