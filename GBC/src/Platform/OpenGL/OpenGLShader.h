#pragma once

#include "GBC/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: remove
typedef unsigned int GLenum;

namespace gbc
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string &path);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		inline virtual const std::string& getName() const override { return name; }

		virtual void setBool(const std::string &name, bool value) override;
		virtual void setInt(const std::string &name, int value) override;
		virtual void setIntArray(const std::string &name, int *values, unsigned int count) override;
		virtual void setFloat(const std::string &name, float value) override;
		virtual void setFloat2(const std::string &name, const glm::vec2 &value) override;
		virtual void setFloat3(const std::string &name, const glm::vec3 &value) override;
		virtual void setFloat4(const std::string &name, const glm::vec4 &value) override;
		virtual void setMat3(const std::string &name, const glm::mat3 &value) override;
		virtual void setMat4(const std::string &name, const glm::mat4 &value) override;
	protected:
		int getUniformLocation(const std::string &name);

		std::string readFile(const std::string &path);
		std::unordered_map<GLenum, std::string> preProcess(const std::string &source);
		void compile(const std::unordered_map<GLenum, std::string> &shaderSources);

		unsigned int rendererID;
		std::string name;
	};
}
