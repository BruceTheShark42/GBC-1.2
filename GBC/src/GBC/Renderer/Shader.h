#pragma once

#include <glm/glm.hpp>

namespace gbc
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setUniform (const std::string& name, float              value) = 0;
		virtual void setUniform (const std::string& name, const glm::vec2&   value) = 0;
		virtual void setUniform (const std::string& name, const glm::vec3&   value) = 0;
		virtual void setUniform (const std::string& name, const glm::vec4&   value) = 0;
		virtual void setUniform (const std::string& name, int                value) = 0;
		virtual void setUniform (const std::string& name, const glm::ivec2&  value) = 0;
		virtual void setUniform (const std::string& name, const glm::ivec3&  value) = 0;
		virtual void setUniform (const std::string& name, const glm::ivec4&  value) = 0;
		virtual void setUniform (const std::string& name, unsigned int       value) = 0;
		virtual void setUniform (const std::string& name, const glm::uvec2&  value) = 0;
		virtual void setUniform (const std::string& name, const glm::uvec3&  value) = 0;
		virtual void setUniform (const std::string& name, const glm::uvec4&  value) = 0;
		virtual void setUniform (const std::string& name, bool               value) = 0;
		virtual void setUniform (const std::string& name, const glm::bvec2&  value) = 0;
		virtual void setUniform (const std::string& name, const glm::bvec3&  value) = 0;
		virtual void setUniform (const std::string& name, const glm::bvec4&  value) = 0;
		virtual void setUniform (const std::string& name, const glm::mat2x2& value) = 0;
		virtual void setUniform (const std::string& name, const glm::mat2x3& value) = 0;
		virtual void setUniform (const std::string& name, const glm::mat2x4& value) = 0;
		virtual void setUniform (const std::string& name, const glm::mat3x2& value) = 0;
		virtual void setUniform (const std::string& name, const glm::mat3x3& value) = 0;
		virtual void setUniform (const std::string& name, const glm::mat3x4& value) = 0;
		virtual void setUniform (const std::string& name, const glm::mat4x2& value) = 0;
		virtual void setUniform (const std::string& name, const glm::mat4x3& value) = 0;
		virtual void setUniform (const std::string& name, const glm::mat4x4& value) = 0;
		virtual void setUniforms(const std::string& name, int*                 values, unsigned int count) = 0;

		virtual const std::string& getName() const = 0;

		static Ref<Shader> create(const std::string& path);
	protected:
		unsigned int rendererID;
	};

	class ShaderLibrary
	{
	public:
		void add(const Ref<Shader>& shader);
		void add(const std::string& name, const Ref<Shader>& shader);

		Ref<Shader> load(const std::string& path);
		Ref<Shader> load(const std::string& name, const std::string& path);

		Ref<Shader> get(const std::string& name);

		bool exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> shaders;
	};
}
