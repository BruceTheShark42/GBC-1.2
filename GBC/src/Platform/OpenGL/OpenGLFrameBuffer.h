#pragma once

#include "GBC/Renderer/Framebuffer.h"

namespace gbc
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecs& specs);
		virtual ~OpenGLFramebuffer();

		void invalidate();

		inline virtual const FramebufferSpecs& getSpecs() const override { return specs; }
		inline virtual unsigned int getColorAttachment() const override { return colorAttachment; }

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void resize(int width, int height) override;
	private:
		unsigned int rendererID = 0;

		// TODO: make this user defined
		unsigned int colorAttachment = 0, depthAttachment = 0;

		FramebufferSpecs specs;
	};
}
