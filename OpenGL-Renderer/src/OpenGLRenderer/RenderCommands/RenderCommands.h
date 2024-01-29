#pragma once

namespace OpenGLRenderer
{
	class RenderCommands
	{
	public:
		static void Clear(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
		static void SetViewport(int x, int y, int width, int height);
		static void EnableDepthTest();
		static void DisableDepthTest();
	};
}