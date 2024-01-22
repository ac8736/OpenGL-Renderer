#pragma once

#include <glm/glm.hpp>
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

		void UploadUniformInt1(int i, const std::string& name) const;

		void UploadUniformFloat1(float i, const std::string& name) const;
		void UploadUniformFloat2(glm::vec2& vec, const std::string& name) const;
		void UploadUniformFloat3(glm::vec3& vec, const std::string& name) const;
		void UploadUniformFloat4(glm::vec4& vec, const std::string& name) const;

		void UploadUniformMat4(glm::mat4& mat, const std::string& name) const;

		static ShaderSource ParseShader(const std::string& filepath);
	private:
		int GetLocation(const std::string& name) const;
		unsigned int CompileShaders(const std::string& source, unsigned int type);
	private:
		std::string m_VertexSource, m_FragmentSource;
		mutable std::unordered_map<std::string, int> m_LocationCache;
		unsigned int m_RendererID;
	};
}

