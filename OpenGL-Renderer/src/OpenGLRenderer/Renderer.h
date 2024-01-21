#pragma once

#include "OpenGLRenderer/VertexArray/VertexArray.h"
#include "OpenGLRenderer/Buffers/Buffer.h"
#include "OpenGLRenderer/Shader/Shader.h"

namespace OpenGLRenderer
{
	class Renderer
	{
	public:
		void Clear();

		void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
	};
}