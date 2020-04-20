#include "gbcpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace gbc
{
	static GLenum shaderToOpenGL(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:  return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3:   return GL_FLOAT;
			case ShaderDataType::Mat4:   return GL_FLOAT;
			case ShaderDataType::Int:    return GL_INT;
			case ShaderDataType::Int2:   return GL_INT;
			case ShaderDataType::Int3:   return GL_INT;
			case ShaderDataType::Int4:   return GL_INT;
			case ShaderDataType::Bool:   return GL_BOOL;
		}

		GBC_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
	{
		GBC_CORE_ASSERT(vertexBuffer->getLayout().getElements().size() != 0, "Vertex buffer has no layout!");

		glBindVertexArray(rendererID);
		vertexBuffer->bind();
		vertexBuffers.push_back(vertexBuffer);

		const BufferLayout &layout = vertexBuffer->getLayout();
		unsigned int index = 0;
		for (auto &element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index++, element.getComponentCount(), shaderToOpenGL(element.type), 
				element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)element.offset);
		}
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
	{
		glBindVertexArray(rendererID);
		indexBuffer->bind();
		this->indexBuffer = indexBuffer;
	}
}
