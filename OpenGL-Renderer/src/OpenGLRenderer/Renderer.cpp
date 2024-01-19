#include "glpch.h"
#include "Renderer.h"

namespace OpenGLRenderer
{
	void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
	{
		shader.Bind();
	}
}