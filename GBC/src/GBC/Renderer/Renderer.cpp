#include "gbcpch.h"
#include "Renderer.h"

namespace gbc
{
	void Renderer::beginScene(const OrthographicCamera &camera)
	{

	}

	void Renderer::endScene()
	{

	}

	void Renderer::submit(const std::shared_ptr<VertexArray> &vertexArray)
	{
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}
