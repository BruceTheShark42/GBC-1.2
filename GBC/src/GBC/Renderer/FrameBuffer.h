#pragma once

#include "GBC/Core/core.h"

namespace gbc
{
	struct FramebufferSpecs
	{
		FramebufferSpecs(int width, int height, int samples = 1, bool swapChainTarget = false)
			: width(width), height(height), samples(samples), swapChainTarget(swapChainTarget) {}

		int width, height, samples;
		bool swapChainTarget;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual const FramebufferSpecs& getSpecs() const = 0;
		virtual unsigned int getColorAttachment() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void resize(int width, int height) = 0;

		static Ref<Framebuffer> create(const FramebufferSpecs& specs);
	};
}
