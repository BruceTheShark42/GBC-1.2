#include "gbcpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace gbc
{
	Ref<VertexBuffer> VertexBuffer::create(float *vertices, unsigned int size)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLVertexBuffer>(vertices, size);
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::create(unsigned int *indices, unsigned int size)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLIndexBuffer>(indices, size);
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}
}
