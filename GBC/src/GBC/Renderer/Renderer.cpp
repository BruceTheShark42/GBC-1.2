#include "gbcpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace gbc
{
	Renderer::SceneData *Renderer::sceneData = new Renderer::SceneData();

	void Renderer::init()
	{
		RenderCommand::init();
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
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniform("projectionView", sceneData->projectionView);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniform("transform", transform);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}
