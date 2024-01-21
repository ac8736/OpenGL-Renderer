#include "glpch.h"

#include "Application.h"
#include "Log/Log.h"
#include "Shader/Shader.h"
#include "Buffers/Buffer.h"
#include "VertexArray/VertexArray.h"
#include "OpenGLRenderer/Renderer.h"
#include "OpenGLRenderer/Texture/Texture.h"

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

		GLFWwindow* window = glfwCreateWindow(1280, 720, "Jason is a clown", NULL, NULL);
		if (!window)
		{
			// Window or OpenGL context creation failed
			CLIENT_WARN("GLFW Create Window Failed!");
			return;
		}

		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status, "Failed to initialize Glad.");

		float positions[4 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};
		
		BufferLayout layout = {
			{ ShaderDataType::Float2, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord"}
		};
		
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(new VertexBuffer(positions, 16));

		vertexBuffer->SetLayout(layout);

		VertexArray vertexArray = VertexArray();
		vertexArray.AddVertexBuffer(vertexBuffer);

		unsigned int indices[] = {
			0, 1, 2, 
			2, 3, 0,
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		IndexBuffer indexBuffer(indices, 6);

		vertexArray.SetIndexBuffer(indexBuffer);

		Shader shader = Shader(Shader::ParseShader("res/shaders/Basic.shader"));
		shader.Bind();
		shader.UploadUniformFloat3(glm::vec3(1.0f, 1.0f, 1.0f), "u_Color");

		Texture texture("res/textures/texture_test.png");
		texture.Bind();
		shader.UploadUniformInt1(0, "u_Texture");

		Renderer renderer;

		while (!glfwWindowShouldClose(window))
		{
			// Keep running
			renderer.Clear();
			renderer.Draw(vertexArray, indexBuffer, shader);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Application::~Application() {}
}
