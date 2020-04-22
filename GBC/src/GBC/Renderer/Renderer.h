#pragma once

#include "RenderCommand.h"
#include "Camera.h"

namespace gbc
{
	class Renderer
	{
	public:
		static void beginScene(const OrthographicCamera &camera);
		static void endScene();

		static void submit(const std::shared_ptr<VertexArray> &vertexArray);

		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	};
}
