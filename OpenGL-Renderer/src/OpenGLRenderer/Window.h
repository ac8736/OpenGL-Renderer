#pragma once

#include "RenderCommands/RenderCommands.h"
#include "Log/Log.h"
#include "Core.h"

struct GLFWwindow;

namespace OpenGLRenderer
{
	class Window
	{
	public:
		Window(int width, int height);

		void SetVsync(bool set);

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		GLFWwindow* GetWindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window = nullptr;
		int m_Width, m_Height;
	};
}

