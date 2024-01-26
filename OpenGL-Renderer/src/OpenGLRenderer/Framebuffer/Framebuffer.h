#pragma once

namespace OpenGLRenderer
{
	class Framebuffer
	{
	public:
		Framebuffer(int width, int height);
		~Framebuffer();

		void Bind();
		void Unbind();

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		void UpdateDimensions(int width, int height);

		unsigned int GetTextureColorID() const { return m_TextureColorID; }
	private:
		int m_Width, m_Height;

		unsigned int m_FramebufferID;
		unsigned int m_TextureColorID;
		unsigned int m_RenderBufferDepthID;
	};
}
