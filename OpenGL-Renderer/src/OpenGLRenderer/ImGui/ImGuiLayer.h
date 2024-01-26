#pragma once

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace OpenGLRenderer
{
	class ImGuiLayer
	{
	public:
		static void Shutdown();

		static void BeginImGui();
		static void EndImGui();

		static void Init(GLFWwindow* window);
	};
}

