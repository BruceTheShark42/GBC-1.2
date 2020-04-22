#pragma once

#include "GBC/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace gbc
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		// TODO: TEMPORARY
		inline void setUniform(const std::string &name, bool value) { setUniform(getUniformLocation(name), value); }
		inline void setUniform(const std::string &name, int value) { setUniform(getUniformLocation(name), value); }
		inline void setUniform(const std::string &name, float value) { setUniform(getUniformLocation(name), value); }
		inline void setUniform(const std::string &name, const glm::vec2 &value) { setUniform(getUniformLocation(name), value); }
		inline void setUniform(const std::string &name, const glm::vec3 &value) { setUniform(getUniformLocation(name), value); }
		inline void setUniform(const std::string &name, const glm::vec4 &value) { setUniform(getUniformLocation(name), value); }
		inline void setUniform(const std::string &name, const glm::mat3 &value) { setUniform(getUniformLocation(name), value); }
		inline void setUniform(const std::string &name, const glm::mat4 &value) { setUniform(getUniformLocation(name), value); }
	protected:
		int getUniformLocation(const std::string &name);

		void setUniform(int location, bool value);
		void setUniform(int location, int value);
		void setUniform(int location, float value);
		void setUniform(int location, const glm::vec2 &value);
		void setUniform(int location, const glm::vec3 &value);
		void setUniform(int location, const glm::vec4 &value);
		void setUniform(int location, const glm::mat3 &value);
		void setUniform(int location, const glm::mat4 &value);

		unsigned int rendererID;
	};
}
