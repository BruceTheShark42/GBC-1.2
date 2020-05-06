#pragma once

#include "GBC/Renderer/RendererAPI.h"

namespace gbc
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void init() override;
		virtual void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
		virtual void clear() override;
		virtual void setClearColor(const glm::vec4 &color) override;

		virtual void drawIndexed(const Ref<VertexArray> &vertexArray, unsigned int count = 0) override;
	};
}
