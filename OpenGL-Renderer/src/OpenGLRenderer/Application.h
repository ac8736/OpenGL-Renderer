#pragma once

#include "Core.h"
#include "Timestep.h"

namespace OpenGLRenderer
{
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		static inline Application& GetApplication() { return *s_Instance; }
	private:
		static Application* s_Instance;
		float m_LastFrameTime = 0.0f;
	};

	Application* CreateApplication();
}
