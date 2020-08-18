#include "gbcpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace gbc
{
	Ref<Shader> Shader::create(const std::string& path)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLShader>(path);
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}


	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
	{
		GBC_CORE_ASSERT(!exists(name), "Shader already exists!");
		shaders[name] = shader;
	}

	void ShaderLibrary::add(const Ref<Shader>& shader)
	{
		auto& name = shader->getName();
		add(name, shader);
	}

	Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& path)
	{
		auto shader = Shader::create(path);
		add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& path)
	{
		auto shader = Shader::create(path);
		add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::get(const std::string& name)
	{
		GBC_CORE_ASSERT(exists(name), "Shader doesn't exist!");
		return shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		return shaders.find(name) != shaders.end();
	}
}
