#include "gbcpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace gbc
{
	VertexBuffer* VertexBuffer::create(float *vertices, unsigned int size)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::create(unsigned int *indices, unsigned int size)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::None: GBC_CORE_ASSERT(false, "Must have a renderer API!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}
		GBC_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}
}
