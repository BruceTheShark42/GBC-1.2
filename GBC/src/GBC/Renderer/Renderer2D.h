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

		// Axis-aligned non-scaled quad
	public:
		inline static void drawQuad(const glm::vec2 &position, const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec4 &color = glm::vec4(1.0f));
		inline static void drawQuad(const glm::vec2 &position, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4  &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4  &color = glm::vec4(1.0f));
	private:
		static void _drawQuad(const glm::vec3 &position, const glm::vec4 &color);

		// Axis-aligned scaled quad
	public:
		inline static void drawQuad(const glm::vec2 &position, const glm::vec2 &scale, const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), scale, color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const glm::vec4 &color = glm::vec4(1.0f));
		inline static void drawQuad(const glm::vec2 &position, const glm::vec2 &scale, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4  &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), scale, texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4  &color = glm::vec4(1.0f));
	private:
		static void _drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const glm::vec4 &color);

		// Non-axis-aligned non-scaled quad
	public:
		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec4 &color = glm::vec4(1.0f));
		inline static void drawQuad(const glm::vec2 &position, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4  &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));
	private:
		static void _drawQuad(const glm::vec3 &position, float rotation, const glm::vec4 &color);

		// Non-axis-aligned scaled quad
	public:
		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, scale, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color = glm::vec4(1.0f));
		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4  &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, scale, texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));
	private:
		static void _drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color);

	// Generic _drawQuad
	private:
		static void _drawQuad(const glm::mat4 &transform, const glm::vec4 &color);
	};
}
