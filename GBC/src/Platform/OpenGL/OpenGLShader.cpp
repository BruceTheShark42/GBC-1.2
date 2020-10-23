#include "gbcpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace gbc
{
	static std::string stringFromShaderType(GLenum type)
	{
		switch (type)
		{
			case GL_VERTEX_SHADER:          return "vertex";
			case GL_TESS_CONTROL_SHADER:    return "tessolation_control";
			case GL_TESS_EVALUATION_SHADER: return "tessolation_evaluation";
			case GL_GEOMETRY_SHADER:        return "geometry";
			case GL_FRAGMENT_SHADER:        return "fragment";
			case GL_COMPUTE_SHADER:	        return "compute";
		}

		GBC_CORE_ASSERT(false, "Unknown shader type!");
		return "unknown";
	}

	static GLenum shaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")                 return GL_VERTEX_SHADER;
		if (type == "tessolation_control")    return GL_TESS_CONTROL_SHADER;
		if (type == "tessolation_evaluation") return GL_TESS_EVALUATION_SHADER;
		if (type == "geometry")               return GL_GEOMETRY_SHADER;
		if (type == "fragment")               return GL_FRAGMENT_SHADER;
		if (type == "compute")                return GL_COMPUTE_SHADER;

		GBC_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& path)
	{
		compile(preProcess(readFile(path)));

		size_t lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = path.rfind('.');
		size_t count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		name = path.substr(lastSlash, count);
	}

	std::string OpenGLShader::readFile(const std::string& path)
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

	std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> sources;

		const char* typeToken = "#type";
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
		}

		return sources;
	}

	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		rendererID = glCreateProgram();
		std::vector<GLenum> shaderIDs;
		shaderIDs.reserve(shaderSources.size());

		for (auto& [type, src] : shaderSources)
		{
			GLuint shader = glCreateShader(type);

			const GLchar* source = (const GLchar*)src.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
#ifdef GBC_ENABLE_LOGGING
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
#endif
				glDeleteShader(shader);

				GBC_CORE_ERROR(infoLog.data());
				GBC_CORE_ASSERT(false, "\"{0}\" shader compilation faliure!", stringFromShaderType(type));
				break;
			}

			glAttachShader(rendererID, shader);
			shaderIDs.push_back(shader);
		}

		glLinkProgram(rendererID);

		GLint isLinked = 0;
		glGetProgramiv(rendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
#ifdef GBC_ENABLE_LOGGING
			GLint maxLength = 0;
			glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]);
#endif
			for (auto shader : shaderIDs)
			{
				glDetachShader(rendererID, shader);
				glDeleteShader(shader);
			}
			glDeleteProgram(rendererID);

			GBC_CORE_ERROR(infoLog.data());
			GBC_CORE_ASSERT(false, "Shader linking faliure!");
			return;
		}

		glValidateProgram(rendererID);

		GLint isValidated = 0;
		glGetProgramiv(rendererID, GL_VALIDATE_STATUS, &isValidated);
		if (isValidated == GL_FALSE)
		{
#ifdef GBC_ENABLE_LOGGING
			GLint maxLength = 0;
			glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]);
#endif
			for (auto shader : shaderIDs)
			{
				glDetachShader(rendererID, shader);
				glDeleteShader(shader);
			}
			glDeleteProgram(rendererID);

			GBC_CORE_ERROR(infoLog.data());
			GBC_CORE_ASSERT(false, "Shader validation faliure!");
			return;
		}

		for (auto shader : shaderIDs)
		{
			glDetachShader(rendererID, shader);
			glDeleteShader(shader);
		}
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

	int OpenGLShader::getUniformLocation(const std::string& name)
	{
		if (uniformLocations.find(name) != uniformLocations.end())
			return uniformLocations[name];

		int location = glGetUniformLocation(rendererID, name.c_str());

		if (location == -1)
			GBC_CORE_WARN("Uniform \"{0}\" does not exist.", name);

		uniformLocations[name] = location;
		return location;
	}

	void OpenGLShader::setUniform(const std::string& name, float              value)
	{ glUniform1fv(getUniformLocation(name), 1,                              &value); }
	void OpenGLShader::setUniform(const std::string& name, const glm::vec2&   value)
	{ glUniform2fv(getUniformLocation(name), 1,                glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::vec3&   value)
	{ glUniform3fv(getUniformLocation(name), 1,                glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::vec4&   value)
	{ glUniform4fv(getUniformLocation(name), 1,                glm::value_ptr(value)); }

	void OpenGLShader::setUniform(const std::string& name, int                value)
	{ glUniform1iv(getUniformLocation(name), 1,                              &value); }
	void OpenGLShader::setUniform(const std::string& name, const glm::ivec2&  value)
	{ glUniform2iv(getUniformLocation(name), 1,                glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::ivec3&  value)
	{ glUniform3iv(getUniformLocation(name), 1,                glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::ivec4&  value)
	{ glUniform4iv(getUniformLocation(name), 1,                glm::value_ptr(value)); }

	void OpenGLShader::setUniform(const std::string& name, unsigned int       value)
	{ glUniform1uiv(getUniformLocation(name), 1,                             &value); }
	void OpenGLShader::setUniform(const std::string& name, const glm::uvec2&  value)
	{ glUniform2uiv(getUniformLocation(name), 1,               glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::uvec3&  value)
	{ glUniform3uiv(getUniformLocation(name), 1,               glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::uvec4&  value)
	{ glUniform4uiv(getUniformLocation(name), 1,               glm::value_ptr(value)); }

	void OpenGLShader::setUniform(const std::string& name, bool               value)
	{ glUniform1iv(getUniformLocation(name), 1, (const int*)&value); }
	void OpenGLShader::setUniform(const std::string& name, const glm::bvec2&  value)
	{ glUniform2iv(getUniformLocation(name), 1,    (const int*)glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::bvec3&  value)
	{ glUniform3iv(getUniformLocation(name), 1,    (const int*)glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::bvec4&  value)
	{ glUniform4iv(getUniformLocation(name), 1,    (const int*)glm::value_ptr(value)); }

	void OpenGLShader::setUniform(const std::string& name, const glm::mat2x2& value)
	{ glUniformMatrix2fv(getUniformLocation(name), 1, false, glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::mat2x3& value)
	{ glUniformMatrix2x3fv(getUniformLocation(name), 1, false, glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::mat2x4& value)
	{ glUniformMatrix2x4fv(getUniformLocation(name), 1, false, glm::value_ptr(value)); }

	void OpenGLShader::setUniform(const std::string& name, const glm::mat3x2& value)
	{ glUniformMatrix3x2fv(getUniformLocation(name), 1, false, glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::mat3x3& value)
	{ glUniformMatrix3fv(getUniformLocation(name), 1, false,   glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::mat3x4& value)
	{ glUniformMatrix3x4fv(getUniformLocation(name), 1, false, glm::value_ptr(value)); }

	void OpenGLShader::setUniform(const std::string& name, const glm::mat4x2& value)
	{ glUniformMatrix4x2fv(getUniformLocation(name), 1, false, glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::mat4x3& value)
	{ glUniformMatrix4x3fv(getUniformLocation(name), 1, false, glm::value_ptr(value)); }
	void OpenGLShader::setUniform(const std::string& name, const glm::mat4x4& value)
	{ glUniformMatrix4fv(getUniformLocation(name), 1, false,   glm::value_ptr(value)); }

	void OpenGLShader::setUniforms(const std::string& name, int*                values, unsigned int count)
	{ glUniform1iv(getUniformLocation(name), count,                             values); }
}
