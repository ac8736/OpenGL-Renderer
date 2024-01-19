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

		GLFWwindow* window = glfwCreateWindow(880, 880, "Jason is a clown", NULL, NULL);
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

		float positions[4 * 2] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		unsigned int indices[] = {
			0, 1, 2, 
			2, 3, 0,
		};

		unsigned int ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		Shader shader = Shader(Shader::ParseShader("res/shaders/Basic.shader"));
		glUseProgram(shader.GetID());

		while (!glfwWindowShouldClose(window))
		{
			// Keep running

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Application::~Application() {}
}
