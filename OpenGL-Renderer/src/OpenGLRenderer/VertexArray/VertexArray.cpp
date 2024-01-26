#include "glpch.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace OpenGLRenderer
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float:  return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3:   return GL_FLOAT;
        case ShaderDataType::Mat4:   return GL_FLOAT;
        case ShaderDataType::Int:    return GL_INT;
        case ShaderDataType::Int2:   return GL_INT;
        case ShaderDataType::Int3:   return GL_INT;
        case ShaderDataType::Int4:   return GL_INT;
        case ShaderDataType::Bool:   return GL_BOOL;
        }

        CORE_ASSERT(false, "Unkown ShaderDataType.");
        return 0;
    }

    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    const IndexBuffer& VertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }

    void VertexArray::AddVertexBuffer(std::shared_ptr<OpenGLRenderer::VertexBuffer>& vertexBuffer)
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

    void VertexArray::SetIndexBuffer(const IndexBuffer& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer.Bind();

        m_IndexBuffer = indexBuffer;
    }
}
