#pragma once

#include "GBC/Core/core.h"

namespace gbc
{
	struct FrameBufferSpecs
	{
		unsigned int width, height, samples = 1;
		bool swapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual const FrameBufferSpecs& getSpecs() const = 0;
		virtual unsigned int getColorAttachment() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Ref<FrameBuffer> create(const FrameBufferSpecs& specs);
	};
}
