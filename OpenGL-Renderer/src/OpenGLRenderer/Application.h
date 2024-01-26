#pragma once

#include "Core.h"
#include "Timestep.h"
#include "Window.h"
#include "Framebuffer/Framebuffer.h"

struct GLFWwindow;

namespace OpenGLRenderer
{
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		virtual void Update() = 0;
		virtual void ImGuiUpdate() = 0;

	protected:
		float m_LastFrameTime = 0.0f;
		Window* m_Window;
	private:
		float CalculateDeltaTime();
	};

	Application* CreateApplication();
}
