#include "gbcpch.h"
#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace gbc
{
	Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			GBC_CORE_ERROR(infoLog.data());
			GBC_CORE_ASSERT(false, "Shader compilation faliure!");
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			glDeleteShader(vertexShader);

			GBC_CORE_ERROR(infoLog.data());
			GBC_CORE_ASSERT(false, "Shader compilation faliure!");
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		rendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(rendererID, vertexShader);
		glAttachShader(rendererID, fragmentShader);

		// Link our program
		glLinkProgram(rendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(rendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(rendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			GBC_CORE_ERROR(infoLog.data());
			GBC_CORE_ASSERT(false, "Shader linking faliure!");
		}

		// Always detach shaders after a successful link.
		glDetachShader(rendererID, vertexShader);
		glDetachShader(rendererID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(rendererID);
	}

	void Shader::bind() const
	{
		glUseProgram(rendererID);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	int Shader::getUniformLocation(const std::string &name)
	{
		return glGetUniformLocation(rendererID, name.c_str());
	}

	void Shader::setUniform(int location, bool value)
	{
		glUniform1i(location, (int)value);
	}

	void Shader::setUniform(int location, int value)
	{
		glUniform1i(location, value);
	}

	void Shader::setUniform(int location, float value)
	{
		glUniform1f(location, value);
	}

	void Shader::setUniform(int location, const glm::vec2 &value)
	{
		glUniform2fv(location, 1, glm::value_ptr(value));
	}

	void Shader::setUniform(int location, const glm::vec3 &value)
	{
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void Shader::setUniform(int location, const glm::vec4 &value)
	{
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void Shader::setUniform(int location, const glm::mat3 &value)
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setUniform(int location, const glm::mat4 &value)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}
