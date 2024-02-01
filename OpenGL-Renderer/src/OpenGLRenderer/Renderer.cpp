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
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
		m_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Draw(std::shared_ptr<VertexArray>& vertexArray, std::shared_ptr<Shader>& shader) const
	{
		shader->Bind();
		shader->UploadUniformMat4(m_SceneData->ViewMatrix, "u_View");
		shader->UploadUniformMat4(m_SceneData->ProjectionMatrix, "u_Projection");

		vertexArray->Bind();

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
