#include "gbcpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace gbc
{
	Ref<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(path);
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::create(unsigned int width, unsigned int height)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(width, height);
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}
}
