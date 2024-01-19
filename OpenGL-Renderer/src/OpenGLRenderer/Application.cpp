#include "glpch.h"

#include "Application.h"
#include "Log/Log.h"
#include "Shader/Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace OpenGLRenderer
{
	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		CORE_ASSERT(!s_Instance, "Application must be singleton.");
		s_Instance = this;
	}

	void Application::Run() 
	{
		if (!glfwInit())
		{
			// Initialization failed
			CLIENT_WARN("GLFW Failed!");
			return;
		}

		GLFWwindow* window = glfwCreateWindow(1280, 720, "My Title", NULL, NULL);
		if (!window)
		{
			// Window or OpenGL context creation failed
			CLIENT_WARN("GLFW Create Window Failed!");
			return;
		}

		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status, "Failed to initialize Glad.");

		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		float positions[3 * 2] = {
			-0.5f, -0.5,
			 0.0f,  0.5f,
			 0.5f, -0.5f
		};

		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		Shader shader = Shader(Shader::ParseShader("res/shaders/Basic.shader"));
		glUseProgram(shader.GetID());

		while (!glfwWindowShouldClose(window))
		{
			// Keep running

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Application::~Application() {}
}
