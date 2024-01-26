#include "glpch.h"
#include "Framebuffer.h"
#include "OpenGLRenderer/RenderCommands/RenderCommands.h"
#include "OpenGLRenderer/Log/Log.h"
#include "OpenGLRenderer/Core.h"

#include <glad/glad.h>

namespace OpenGLRenderer
{
	Framebuffer::Framebuffer(int width, int height) : m_Width(width), m_Height(height)
	{
		glGenFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

		// Create and attach a texture as the color attachment
		glGenTextures(1, &m_TextureColorID);
		glBindTexture(GL_TEXTURE_2D, m_TextureColorID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureColorID, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderBufferDepthID);
		glBindTexture(GL_TEXTURE_2D, m_RenderBufferDepthID);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Width, m_Height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_RenderBufferDepthID, 0);

		CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete.");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_FramebufferID);
	}

	void Framebuffer::Bind()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::UpdateDimensions(int width, int height)
	{
		// Assuming framebuffer, textureColor, and renderbufferDepth are already created
		glBindTexture(GL_TEXTURE_2D, m_TextureColorID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glBindTexture(GL_TEXTURE_2D, m_RenderBufferDepthID);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_RenderBufferDepthID, 0);
		CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete.");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
