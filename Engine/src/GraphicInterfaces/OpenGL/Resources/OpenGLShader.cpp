#include "GraphicInterfaces/OpenGL/Resources/OpenGLShader.h"
#include "Core/Logger/Logger.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

namespace ENGINE_NAMESPACE
{
	OpenGLShader::OpenGLShader(const CString& filePath)
		:m_FilePath(filePath)
	{
		CreateShader();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ShaderID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const CString& name, int value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetIntArray(const CString& name, int* values, uint32 count)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetFloat(const CString& name, float value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetFloat2(const CString& name, const vec2& value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const CString& name, const vec3& value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const CString& name, const vec4& value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat3(const CString& name, const mat3& value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4(const CString& name, const mat4& value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::Reload()
	{
		LOG_CORE_INFO("Reloaded Shader ", m_FilePath);
		glDeleteProgram(m_ShaderID);
		CreateShader();
	}

	void OpenGLShader::CreateShader()
	{
		auto shaderSources = ReadFile(m_FilePath);

		uint32 vertex = glCreateShader(GL_VERTEX_SHADER);
		uint32 fragment = glCreateShader(GL_FRAGMENT_SHADER);
		//@todo: create other shaders too

		const char* vs = shaderSources[ShaderType::VERTEX].c_str();
		const char* fs = shaderSources[ShaderType::FRAGMENT].c_str();
		//const char* gs = shaderSources[GL_GEOMETRY_SHADER].c_str();

		glShaderSource(vertex, 1, &vs, nullptr);
		glShaderSource(fragment, 1, &fs, nullptr);

		glCompileShader(vertex);
		glCompileShader(fragment);
		CheckErrors(vertex, "VERTEX");
		CheckErrors(fragment, "FRAGMENT");

		m_ShaderID = glCreateProgram();

		glAttachShader(m_ShaderID, vertex);
		glAttachShader(m_ShaderID, fragment);
		glLinkProgram(m_ShaderID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		auto lastSlash = m_FilePath.find_last_of("/\\");
		lastSlash = lastSlash == CString::npos ? 0 : lastSlash + 1;
		auto lastDot = m_FilePath.find('.');
		auto count = lastDot == CString::npos ? m_FilePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = m_FilePath.substr(lastSlash, count);
	}

	CUnorderedMap<ShaderType, CString> OpenGLShader::ReadFile(const CString& filepath)
	{
		ShaderType type = ShaderType::NONE;

		CUnorderedMap<ShaderType, CString> shaderSources;
		std::ifstream file(filepath);

		if (file)
		{
			CString line;
			std::stringstream ss[3];
			while (std::getline(file, line))
			{
				if (line.find("#shader") != CString::npos)
				{
					if (line.find("vertex") != CString::npos) type = ShaderType::VERTEX;
					else if (line.find("fragment") != CString::npos) type = ShaderType::FRAGMENT;
					else if (line.find("geometry") != CString::npos) type = ShaderType::GEOMETRY;
				}
				else
				{
					ss[(int)type] << line << '\n';
				}
			}
			file.close();

			shaderSources[ShaderType::VERTEX] = ss[(int)ShaderType::VERTEX].str();
			shaderSources[ShaderType::FRAGMENT] = ss[(int)ShaderType::FRAGMENT].str();
			//shaderSources[ShaderType::GEOMETRY] = ss[(int)ShaderType::GEOMETRY].str();
		}
		else
		{
			LOG_CORE_ERROR("Could not open file: ", filepath);
		}

		return shaderSources;
	}

	void OpenGLShader::CheckErrors(const unsigned int& shader, const char* name)
	{
		int status = GL_TRUE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			int loglen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen);
			CVector<char> log;
			log.reserve(loglen);
			GLsizei written = 0;
			glGetShaderInfoLog(shader, loglen, &written, log.data());
			LOG_CORE_ERROR("Failed to compile ", name, " shader: ", log.data());
		}
	}
}