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
		static void flush();

		// drawQuad
	private:
		static void createQuad(const glm::vec3 &position, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color);
		static void createQuad(const glm::vec3 &position, float rotation, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color);
		static void createQuad(const glm::vec3 &position, const glm::vec2 &scale, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color);
		static void createQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color);
	public:
		// Non-rotated non-scaled quad
		inline static void drawQuad(const glm::vec2 &position, const glm::vec4 &color)
		{ drawQuad(glm::vec3(position, 0.0f), color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec4 &color);
		inline static void drawQuad(const glm::vec2 &position, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));

		// Non-rotated scaled quad
		inline static void drawQuad(const glm::vec2 &position, const glm::vec2 &scale, const glm::vec4 &color)
		{ drawQuad(glm::vec3(position, 0.0f), scale, color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const glm::vec4 &color);
		inline static void drawQuad(const glm::vec2 &position, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), scale, texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
		
		// Rotated non-scaled quad
		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec4 &color)
		{ drawQuad(glm::vec3(position, 0.0f), rotation, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec4 &color);
		inline static void drawQuad(const glm::vec2 &position, float rotation, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));

		// Rotated scaled quad
		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color)
		{ drawQuad(glm::vec3(position, 0.0f), rotation, scale, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color);
		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, scale, texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
	};
}
