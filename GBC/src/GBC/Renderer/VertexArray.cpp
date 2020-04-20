#include "gbcpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace gbc
{
	VertexArray* VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}
}
