#pragma once

#include <GLFW/glfw3.h>

namespace OpenGLRenderer
{
	class Input
	{
	public:
		static bool IsKeyPressed(int keycode, GLFWwindow* window);
		static bool IsMousePressed(int mousecode, GLFWwindow* window);
	};
}