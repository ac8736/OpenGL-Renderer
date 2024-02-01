#include "glpch.h"
#include "Window.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

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

		glfwSetWindowUserPointer(m_Window, &m_Data);

		// setting up glfw callbacks; which calls the EventCallback function inside the WindowData struct with the event triggered
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;

			data.EventCallback(event);
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent mousePressed(button);
					data.EventCallback(mousePressed);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent mouseReleased(button);
					data.EventCallback(mouseReleased);
					break;
				}
			}
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent keyPressed(key, 0);
					data.EventCallback(keyPressed);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent keyReleased(key);
					data.EventCallback(keyReleased);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent keyRepeat(key, 1);
					data.EventCallback(keyRepeat);
					break;
				}
			}
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int character) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(character);
			data.EventCallback(event);
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});
	}

	void Window::SetVsync(bool set)
	{
		glfwSwapInterval(set ? 1 : 0);
	}
}