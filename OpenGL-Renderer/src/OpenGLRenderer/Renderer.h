#pragma once

#include "OpenGLRenderer/VertexArray/VertexArray.h"
#include "OpenGLRenderer/Buffers/Buffer.h"
#include "OpenGLRenderer/Shader/Shader.h"
#include "OpenGLRenderer/Camera/Camera.h"

namespace OpenGLRenderer
{
	class Renderer
	{
	public:
		void BeginScene(Camera& camera);
		void EndScene();

		void Clear();

		void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}