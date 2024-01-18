#include "Application.h"
#include "Log/Log.h"

namespace OpenGLRenderer
{
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		CORE_ASSERT(!s_Instance, "Application must be singleton.");
		s_Instance = this;
	}

	void Application::Run() 
	{
		CORE_TRACE("Running");
	}

	Application::~Application() {}
}