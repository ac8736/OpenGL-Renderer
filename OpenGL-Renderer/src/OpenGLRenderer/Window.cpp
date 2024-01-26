#include "glpch.h"
#include "Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace OpenGLRenderer
{
	Window::Window(int width, int height) : m_Width(width), m_Height(height)
	{
		if (!glfwInit())
		{
			// Initialization failed
			CORE_ASSERT(true, "GLFW Failed!");
			return;
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, "OpenGL Renderer", NULL, NULL);
		if (!m_Window)
		{
			// Window or OpenGL context creation failed
			CORE_ASSERT(m_Window, "GLFW Create Window Failed!");
			return;
		}

		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status, "Failed to initialize Glad.");

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			RenderCommands::SetViewport(0, 0, width, height);
		});
	}

	void Window::SetVsync(bool set)
	{
		if (set)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}
}