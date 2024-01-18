#pragma once

#include "Core.h"

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
	};

	Application* CreateApplication();
}