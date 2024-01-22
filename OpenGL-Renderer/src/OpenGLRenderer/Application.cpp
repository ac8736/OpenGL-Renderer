#include "glpch.h"

#include "Application.h"
#include "Log/Log.h"
#include "Shader/Shader.h"
#include "Buffers/Buffer.h"
#include "VertexArray/VertexArray.h"
#include "OpenGLRenderer/Renderer.h"
#include "OpenGLRenderer/Texture/Texture.h"
#include "OpenGLRenderer/Camera/OrthographicCamera.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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

		GLFWwindow* window = glfwCreateWindow(880, 880, "OpenGL Renderer", NULL, NULL);
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

		IndexBuffer indexBuffer(indices, 6);

		vertexArray.SetIndexBuffer(indexBuffer);

		Shader shader = Shader(Shader::ParseShader("res/shaders/Basic.shader"));
		shader.Bind();
		shader.UploadUniformFloat3(glm::vec3(1.0f, 1.0f, 1.0f), "u_Color");

		Texture texture("res/textures/texture_test.png");
		texture.EnableBlend();
		texture.Bind();
		shader.UploadUniformInt1(0, "u_Texture");

		Renderer renderer;

		OrthographicCamera camera(-1.0f, 1.0f, 1.0f, -1.0f);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");

		while (!glfwWindowShouldClose(window))
		{
			float currentTime = (float)glfwGetTime();
			Timestep timestamp = currentTime - m_LastFrameTime;
			m_LastFrameTime = currentTime;
			float tsSeconds = timestamp.GetSeconds();

			renderer.BeginScene(camera);
			renderer.Clear();
			renderer.Draw(vertexArray, indexBuffer, shader);
			renderer.EndScene();


			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Application::~Application() {}
}
