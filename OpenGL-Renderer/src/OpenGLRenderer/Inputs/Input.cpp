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
}
