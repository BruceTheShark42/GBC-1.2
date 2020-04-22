#pragma once

#include "GBC/Renderer/RendererAPI.h"

namespace gbc
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void clear() override;
		virtual void setClearColor(const glm::vec4 &color) override;

		virtual void drawIndexed(const Ref<VertexArray> &vertexArray) override;
	};
}
