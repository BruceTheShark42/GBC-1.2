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
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void setUniform (const std::string& name, float              value) override;
		virtual void setUniform (const std::string& name, const glm::vec2&   value) override;
		virtual void setUniform (const std::string& name, const glm::vec3&   value) override;
		virtual void setUniform (const std::string& name, const glm::vec4&   value) override;
		virtual void setUniform (const std::string& name, int                value) override;
		virtual void setUniform (const std::string& name, const glm::ivec2&  value) override;
		virtual void setUniform (const std::string& name, const glm::ivec3&  value) override;
		virtual void setUniform (const std::string& name, const glm::ivec4&  value) override;
		virtual void setUniform (const std::string& name, unsigned int       value) override;
		virtual void setUniform (const std::string& name, const glm::uvec2&  value) override;
		virtual void setUniform (const std::string& name, const glm::uvec3&  value) override;
		virtual void setUniform (const std::string& name, const glm::uvec4&  value) override;
		virtual void setUniform (const std::string& name, bool               value) override;
		virtual void setUniform (const std::string& name, const glm::bvec2&  value) override;
		virtual void setUniform (const std::string& name, const glm::bvec3&  value) override;
		virtual void setUniform (const std::string& name, const glm::bvec4&  value) override;
		virtual void setUniform (const std::string& name, const glm::mat2x2& value) override;
		virtual void setUniform (const std::string& name, const glm::mat2x3& value) override;
		virtual void setUniform (const std::string& name, const glm::mat2x4& value) override;
		virtual void setUniform (const std::string& name, const glm::mat3x2& value) override;
		virtual void setUniform (const std::string& name, const glm::mat3x3& value) override;
		virtual void setUniform (const std::string& name, const glm::mat3x4& value) override;
		virtual void setUniform (const std::string& name, const glm::mat4x2& value) override;
		virtual void setUniform (const std::string& name, const glm::mat4x3& value) override;
		virtual void setUniform (const std::string& name, const glm::mat4x4& value) override;
		virtual void setUniforms(const std::string& name, int*                 values, unsigned int count) override;

		inline virtual const std::string& getName() const override { return name; }
	protected:
		int getUniformLocation(const std::string& name);

		std::string readFile(const std::string& path);
		std::unordered_map<GLenum, std::string> preProcess(const std::string& source);
		void compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		unsigned int rendererID;
		std::string name;
		std::unordered_map<std::string, int> uniformLocations;
	};
}
