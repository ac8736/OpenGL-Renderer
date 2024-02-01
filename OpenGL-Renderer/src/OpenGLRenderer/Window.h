#pragma once

#include "RenderCommands/RenderCommands.h"
#include "Log/Log.h"
#include "Core.h"
#include "Events/Event.h"

struct GLFWwindow;

namespace OpenGLRenderer
{
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(int width, int height);

		void SetVsync(bool set);

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		GLFWwindow* GetWindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window = nullptr;
		int m_Width, m_Height;

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}

