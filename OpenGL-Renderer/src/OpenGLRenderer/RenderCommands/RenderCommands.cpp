#include "glpch.h"
#include "RenderCommands.h"

#include <glad/glad.h>

namespace OpenGLRenderer
{
	void RenderCommands::Clear(float x, float y, float z, float w)
	{
		glClearColor(x, y, z, w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderCommands::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}
}
