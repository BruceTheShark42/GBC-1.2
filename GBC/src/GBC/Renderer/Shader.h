#pragma once

#include <string>
#include <glm/glm.hpp>

namespace gbc
{
	class Shader
	{
	public:
		Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
		~Shader();

		void bind() const;
		void unbind() const;

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
