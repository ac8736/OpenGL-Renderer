#include "glpch.h"
#include "Input.h"

#include <GLFW/glfw3.h>

namespace OpenGLRenderer
{
	bool Input::IsKeyPressed(int keycode, GLFWwindow* window)
	{
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMousePressed(int mousecode, GLFWwindow* window)
	{
		int state = glfwGetMouseButton(window, mousecode);
		return state == GLFW_PRESS;
	}

	float Input::GetMousePosX(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return (float)x;
	}

	float Input::GetMousePosY(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return (float)y;
	}
}
