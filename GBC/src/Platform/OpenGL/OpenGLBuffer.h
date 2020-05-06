#pragma once

#include "GBC/Renderer/Buffer.h"

namespace gbc
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float *vertices, unsigned int size);
		OpenGLVertexBuffer(unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		inline virtual const BufferLayout& getLayout() const override { return layout; }
		inline virtual void setLayout(const BufferLayout &layout) override { this->layout = layout; }

		virtual void setData(const void *data, unsigned int size) override;
	private:
		unsigned int rendererID;
		BufferLayout layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int *indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual unsigned int getCount() const override { return count; }
	private:
		unsigned int rendererID, count;
	};
}
