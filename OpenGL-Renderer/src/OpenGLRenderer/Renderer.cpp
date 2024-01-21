#include "glpch.h"
#include "Renderer.h"

namespace OpenGLRenderer
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetProjectionViewMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
	{
		shader.Bind();
		shader.UploadUniformMat4(m_SceneData->ViewProjectionMatrix, "u_ViewProjectionMatrix");

		vertexArray.Bind();
		vertexArray.GetIndexBuffer().Bind();

		glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
