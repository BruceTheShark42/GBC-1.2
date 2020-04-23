#pragma once

#include "RendererAPI.h"

namespace gbc
{
	class RenderCommand
	{
	public:
		inline static void init()
		{
			api->init();
		}
		
		inline static void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
		{
			api->setViewport(x, y, width, height);
		}

		inline static void clear()
		{
			api->clear();
		}

		inline static void setClearColor(const glm::vec4 &color)
		{
			api->setClearColor(color);
		}

		inline static void drawIndexed(const Ref<VertexArray>& vertexArray)
		{
			api->drawIndexed(vertexArray);
		}
	private:
		static RendererAPI *api;
	};
}
