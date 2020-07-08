#include "gbcpch.h"
#include "FrameBuffer.h"
#include "GBC/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace gbc
{
	Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpecs &specs)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLFrameBuffer>(specs);
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}
}
