#pragma once

#include "Camera.h"
#include "Texture.h"

namespace gbc
{
	class Renderer2D
	{
	public:
		static void init();
		static void shutdown();

		static void beginScene(const OrthographicCamera &camera);
		static void endScene();
		
		static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &size, const glm::vec4 &color);
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &size, const glm::vec4 &color);
		static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &size, const Ref<Texture2D> &texture, const glm::vec4 &tint = glm::vec4(0.0f));
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &size, const Ref<Texture2D> &texture, const glm::vec4 &tint = glm::vec4(0.0f));
	};
}
