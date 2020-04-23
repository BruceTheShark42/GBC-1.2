#include "gbcpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace gbc
{
	Ref<VertexArray> VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLVertexArray>();
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}
}
