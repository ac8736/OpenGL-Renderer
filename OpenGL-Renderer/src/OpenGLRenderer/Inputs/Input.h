#pragma once

struct GLFWwindow;

namespace OpenGLRenderer
{
	class Input
	{
	public:
		static bool IsKeyPressed(int keycode, GLFWwindow* window);
		static bool IsMousePressed(int mousecode, GLFWwindow* window);

		static float GetMousePosX(GLFWwindow* window);
		static float GetMousePosY(GLFWwindow* window);

		static float GetMouseScrollY(GLFWwindow* window);
	};
}
