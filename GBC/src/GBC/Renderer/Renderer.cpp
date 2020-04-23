#include "gbcpch.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace gbc
{
	Renderer::SceneData *Renderer::sceneData = new Renderer::SceneData();

	void Renderer::init()
	{
		RenderCommand::init();
		Renderer2D::init();
	}

	void Renderer::onWindowResized(unsigned int width, unsigned int height)
	{
		RenderCommand::setViewport(0, 0, width, height);
	}

	void Renderer::beginScene(const OrthographicCamera &camera)
	{
		sceneData->projectionView = camera.getProjectionView();
	}

	void Renderer::endScene()
	{

	}

	void Renderer::submit(const Ref<VertexArray> &vertexArray, const Ref<Shader> &shader, const glm::mat4 &transform)
	{
		shader->bind();
		shader->setMat4("projectionView", sceneData->projectionView);
		shader->setMat4("transform", transform);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}
