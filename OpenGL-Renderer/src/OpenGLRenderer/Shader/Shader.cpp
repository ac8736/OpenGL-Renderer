#include "glpch.h"
#include "Shader.h"
#include "OpenGLRenderer/Log/Log.h"
#include "OpenGLRenderer/Core.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace OpenGLRenderer
{
	Shader::Shader(const ShaderSource& shaderSource)
		: m_VertexSource(shaderSource.VertexSource), m_FragmentSource(shaderSource.FragmentSource)
	{
		unsigned int program = glCreateProgram();
		m_RendererID = program;

		unsigned int vs = CompileShaders(m_VertexSource, GL_VERTEX_SHADER);
		unsigned int fs = CompileShaders(m_FragmentSource, GL_FRAGMENT_SHADER);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	ShaderSource Shader::ParseShader(const std::string& filepath)
	{
		enum ShaderType
		{
			None = -1, Vertex = 0, Fragment = 1
		};

		std::stringstream ss[2];
		std::ifstream shaderFile(filepath);
		if (shaderFile.is_open())
		{
			std::string line;
			ShaderType type = ShaderType::None;
			while (std::getline(shaderFile, line))
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (line.find("vertex") != std::string::npos)
					{
						type = ShaderType::Vertex;
					}
					else if (line.find("fragment") != std::string::npos)
					{
						type = ShaderType::Fragment;
					}
				}
				else
				{
					ss[type] << line << "\n";
				}
			}
		}
		else
		{
			CORE_WARN("Unable to open shader file: {0}", filepath);
		}

		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::CompileShaders(const std::string& source, unsigned int type)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(id);

			// Use the infoLog as you see fit.
			CORE_ERROR("{0}", infoLog.data());
			CORE_ASSERT(false, "Shader compilation error!");
			
			return 0;
		}

		return id;
	}

	int Shader::GetLocation(const std::string& name) const
	{
		if (m_LocationCache.find(name) != m_LocationCache.end())
		{
			return m_LocationCache[name];
		}
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		m_LocationCache[name] = location;
		return location;
	}

	void Shader::UploadUniformInt1(int i, const std::string& name) const
	{
		glUniform1i(GetLocation(name), i);
	}

	void Shader::UploadUniformFloat1(float i, const std::string& name) const
	{
		glUniform1f(GetLocation(name), i);
	}

	void Shader::UploadUniformFloat2(const glm::vec2& vec, const std::string& name) const
	{
		glUniform2f(GetLocation(name), vec.x, vec.y);
	}

	void Shader::UploadUniformFloat3(const glm::vec3& vec, const std::string& name) const
	{
		glUniform3f(GetLocation(name), vec.x, vec.y, vec.z);
	}

	void Shader::UploadUniformFloat4(const glm::vec4& vec, const std::string& name) const
	{
		glUniform4f(GetLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::UploadUniformMat4(const glm::mat4& mat, const std::string& name) const
	{
		glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
	}
}