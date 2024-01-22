#pragma once

#include <stb_image.h>
#include <glad/glad.h>

namespace OpenGLRenderer
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		void ChangeTexture(const std::string& path);

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		void EnableBlend() const;
		void DisableBlend() const;
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	};
}