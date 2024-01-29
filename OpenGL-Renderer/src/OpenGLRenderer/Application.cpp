#include "glpch.h"

#include "Application.h"
#include "Log/Log.h"
#include "Shader/Shader.h"
#include "Buffers/Buffer.h"
#include "VertexArray/VertexArray.h"
#include "OpenGLRenderer/Renderer.h"
#include "OpenGLRenderer/Texture/Texture.h"
#include "OpenGLRenderer/Camera/OrthographicCamera.h"
#include "OpenGLRenderer/ImGui/ImGuiLayer.h"
#include "OpenGLRenderer/Inputs/Input.h"
#include "OpenGLRenderer/RenderCommands/RenderCommands.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

namespace OpenGLRenderer
{
	Application::Application() : m_Window(new Window(1280, 720))
	{
		m_Window->SetVsync(true);
		RenderCommands::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

		ImGuiLayer::Init(m_Window->GetWindow());
	}

	void Application::Run() 
	{
		while (!glfwWindowShouldClose(m_Window->GetWindow()))
		{
			CalculateDeltaTime();

			ImGuiLayer::BeginImGui();
			Update();
			ImGuiUpdate();
			ImGuiLayer::EndImGui();

			glfwSwapBuffers(m_Window->GetWindow());
			glfwPollEvents();
		}

		ImGuiLayer::Shutdown();
		glfwDestroyWindow(m_Window->GetWindow());
		glfwTerminate();
	}

	void Application::CalculateDeltaTime()
	{
		float currentTime = (float)glfwGetTime();
		Timestep timestamp = currentTime - m_LastFrameTime;
		m_LastFrameTime = currentTime;
		m_DeltaTime = timestamp.GetSeconds();
	}

	float Application::GetTime()
	{
		return (float)glfwGetTime();
	}

	Application::~Application() 
	{
		delete m_Window;
		m_Window = nullptr;
	}
}
