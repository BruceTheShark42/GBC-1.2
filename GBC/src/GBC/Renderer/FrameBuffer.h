#pragma once

#include "GBC/Core/core.h"

namespace gbc
{
	struct FrameBufferSpecs
	{
		FrameBufferSpecs(unsigned int width, unsigned int height, unsigned int samples = 1, bool swapChainTarget = false)
			: width(width), height(height), samples(samples), swapChainTarget(swapChainTarget) {}

		unsigned int width, height, samples;
		bool swapChainTarget;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual const FrameBufferSpecs& getSpecs() const = 0;
		virtual unsigned int getColorAttachment() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void resize(unsigned int width, unsigned int height) = 0;

		static Ref<FrameBuffer> create(const FrameBufferSpecs& specs);
	};
}
