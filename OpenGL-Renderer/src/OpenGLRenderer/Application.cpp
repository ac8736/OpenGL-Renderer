#include "glpch.h"

#include "Application.h"
#include "Log/Log.h"
#include "Shader/Shader.h"
#include "Buffers/Buffer.h"
#include "VertexArray/VertexArray.h"

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

		float positions[4 * 2] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};
		
		BufferLayout layout = {
			{ ShaderDataType::Float2, "a_Position" }
		};
		
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(new VertexBuffer(positions, 8));

		vertexBuffer->SetLayout(layout);

		VertexArray vertexArray = VertexArray();
		vertexArray.AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = {
			0, 1, 2, 
			2, 3, 0,
		};

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(new IndexBuffer(indices, 6));

		vertexArray.SetIndexBuffer(indexBuffer);

		Shader shader = Shader(Shader::ParseShader("res/shaders/Basic.shader"));
		shader.Bind();

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
