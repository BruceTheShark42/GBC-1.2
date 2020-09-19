#include "gbcpch.h"
#include "Framebuffer.h"
#include "GBC/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace gbc
{
	Ref<Framebuffer> Framebuffer::create(const FramebufferSpecs& specs)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLFramebuffer>(specs);
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}
}
