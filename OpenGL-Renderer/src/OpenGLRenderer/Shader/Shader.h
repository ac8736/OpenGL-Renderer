#pragma once

#include <glad/glad.h>

namespace OpenGLRenderer
{
	struct ShaderSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader(const ShaderSource& shaderSource);

		~Shader();

		void Bind() const;

		const unsigned int GetID() const { return m_RendererID; }

		static ShaderSource ParseShader(const std::string& filepath);
	private:
		unsigned int CompileShaders(const std::string& source, unsigned int type);
	private:
		std::string m_VertexSource, m_FragmentSource;
		unsigned int m_RendererID;
	};
}

