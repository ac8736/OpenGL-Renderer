#include "glpch.h"
#include "Renderer.h"
#include "RenderCommands/RenderCommands.h"

#include <glad/glad.h>

namespace OpenGLRenderer
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(Camera& camera)
	{
		RenderCommands::Clear();
		m_SceneData->ViewProjectionMatrix = camera.GetProjectionViewMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Draw(std::shared_ptr<VertexArray>& vertexArray, std::shared_ptr<Shader>& shader) const
	{
		shader->Bind();
		// shader->UploadUniformMat4(m_SceneData->ViewProjectionMatrix, "u_ViewProjectionMatrix");

		vertexArray->Bind();

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
