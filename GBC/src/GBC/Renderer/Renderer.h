#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"

namespace gbc
{
	class Renderer
	{
	public:
		static void init();

		static void beginScene(const OrthographicCamera &camera);
		static void endScene();

		static void submit(const Ref<VertexArray> &vertexArray, const Ref<Shader> &shader, const glm::mat4 &transform = glm::mat4(1.0f));

		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 projectionView;
		};
		static SceneData *sceneData;
	};
}
