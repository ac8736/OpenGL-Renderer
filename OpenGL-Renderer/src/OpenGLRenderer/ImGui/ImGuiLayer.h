#pragma once

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace OpenGLRenderer
{
	class ImGuiLayer
	{
	public:
		ImGuiLayer() {}

		void Init(GLFWwindow* window);

		void BeginImGui();
		void EndImGui();
	private:

	};
}

