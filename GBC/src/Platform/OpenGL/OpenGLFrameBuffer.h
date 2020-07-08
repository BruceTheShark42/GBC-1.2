#pragma once

#include "GBC/Renderer/FrameBuffer.h"

namespace gbc
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecs &specs);
		virtual ~OpenGLFrameBuffer();

		void invalidate();

		inline virtual const FrameBufferSpecs& getSpecs() const override { return specs; }
		inline virtual unsigned int getColorAttachment() const override { return colorAttachment; }

		virtual void bind() const override;
		virtual void unbind() const override;
	private:
		unsigned int rendererID;

		// TODO: make this user defined
		unsigned int colorAttachment, depthAttachment;

		FrameBufferSpecs specs;
	};
}
