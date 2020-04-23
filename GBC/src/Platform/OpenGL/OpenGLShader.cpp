#include "gbcpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace gbc
{
	static GLenum shaderTypeFromString(const std::string &type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "geometry") return GL_GEOMETRY_SHADER;
		if (type == "fragment") return GL_FRAGMENT_SHADER;

		GBC_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string &path)
	{
		compile(preProcess(readFile(path)));

		size_t lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = path.rfind('.');
		size_t count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		name = path.substr(lastSlash, count);
	}

	std::string OpenGLShader::readFile(const std::string &path)
	{
		std::string shaders;
		std::ifstream file(path, std::ios::in | std::ios::binary);
		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			shaders.resize(file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&shaders[0], shaders.size());
			file.close();
		}
		else
			GBC_CORE_ASSERT(false, "Couldn't find shader file!");
		return shaders;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string &source)
	{
		std::unordered_map<GLenum, std::string> sources;

		const char *typeToken = "#type";
		size_t typeTokenLength = std::strlen(typeToken);
		size_t pos = source.find(typeToken);
		
		while (pos != std::string::npos)
		{
			size_t lineEnd = source.find_first_of("\r\n", pos);
			GBC_CORE_ASSERT(lineEnd != std::string::npos, "Empty shader section!");

			size_t typeBegin = pos + typeTokenLength + 1;
			GLenum type = shaderTypeFromString(source.substr(typeBegin, lineEnd - typeBegin));

			size_t nextLinePos = source.find_first_not_of("\r\n", lineEnd);
			pos = source.find(typeToken, nextLinePos);
			sources[type] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));

			GBC_CORE_TRACE("npos={0} pos={1}", std::string::npos, pos);
		}

		return sources;
	}

	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string> &shaderSources)
	{
		rendererID = glCreateProgram();
		std::vector<GLenum> shaderIDs;
		shaderIDs.reserve(shaderSources.size());

		for (auto &kv : shaderSources)
		{
			const GLenum type = kv.first;
			const std::string &src = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar *source = (const GLchar*)src.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				GBC_CORE_ERROR(infoLog.data());
				GBC_CORE_ASSERT(false, "Shader compilation faliure!");
				break;
			}

			glAttachShader(rendererID, shader);
			shaderIDs.push_back(shader);
		}

		glLinkProgram(rendererID);

		GLint isLinked = 0;
		glGetProgramiv(rendererID, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(rendererID);

			for (auto shader : shaderIDs)
				glDeleteShader(shader);

			GBC_CORE_ERROR(infoLog.data());
			GBC_CORE_ASSERT(false, "Shader linking faliure!");
			return;
		}

		for (auto shader : shaderIDs)
			glDetachShader(rendererID, shader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(rendererID);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(rendererID);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}

	int OpenGLShader::getUniformLocation(const std::string &name)
	{
		return glGetUniformLocation(rendererID, name.c_str());
	}

	void OpenGLShader::setUniform(int location, bool value)
	{
		glUniform1i(location, (int)value);
	}

	void OpenGLShader::setUniform(int location, int value)
	{
		glUniform1i(location, value);
	}

	void OpenGLShader::setUniform(int location, float value)
	{
		glUniform1f(location, value);
	}

	void OpenGLShader::setUniform(int location, const glm::vec2 &value)
	{
		glUniform2fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::setUniform(int location, const glm::vec3 &value)
	{
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::setUniform(int location, const glm::vec4 &value)
	{
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::setUniform(int location, const glm::mat3 &value)
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::setUniform(int location, const glm::mat4 &value)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}
