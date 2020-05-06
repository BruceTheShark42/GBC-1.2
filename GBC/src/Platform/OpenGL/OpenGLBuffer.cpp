#include "gbcpch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace gbc
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, unsigned int size)
	{
		glCreateBuffers(1, &rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size)
	{
		glCreateBuffers(1, &rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}

	void OpenGLVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::setData(const void *data, unsigned int size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}


	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int *indices, unsigned int count)
		: count(count)
	{
		glCreateBuffers(1, &rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	}

	void OpenGLIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
