#pragma once

#include "Camera.h"
#include "SubTexture2D.h"

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
	private:
		static void ensureBatch();
		
		// Stats
#ifdef GBC_ENABLE_STATS
	public:
		struct Statistics
		{
			unsigned int drawCalls, quadCount;

			unsigned int getVertexCount() const { return quadCount * 4; }
			unsigned int getIndexCount() const { return quadCount * 6; }
		};

		static const Statistics& getStats();
		static void resetStats();
#endif

	private:
		// drawQuad
		static void createQuad(const glm::vec3 &position, const glm::vec2 *texCoords, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color);
		static void createQuad(const glm::vec3 &position, float rotation, const glm::vec2 *texCoords, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color);
		static void createQuad(const glm::vec3 &position, const glm::vec2 &scale, const glm::vec2 *texCoords, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color);
		static void createQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const glm::vec2 *texCoords, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color);
	public:
		// Non-rotated non-scaled quad
		inline static void drawQuad(const glm::vec2 &position, const glm::vec4 &color)
		{ drawQuad(glm::vec3(position, 0.0f), color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec4 &color);
		
		inline static void drawQuad(const glm::vec2 &position, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
		
		inline static void drawQuad(const glm::vec2 &position, const Ref<SubTexture2D> &subtexture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), subtexture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, const Ref<SubTexture2D> &subtexture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
	private:
		static void _drawQuad(const glm::vec3 &position, const Ref<Texture2D> &texture, const glm::vec2 *texCoords, const glm::vec2 &tilingFactor, const glm::vec4 &color);

	public:
		// Rotated non-scaled quad
		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec4 &color)
		{ drawQuad(glm::vec3(position, 0.0f), rotation, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec4 &color);
		
		inline static void drawQuad(const glm::vec2 &position, float rotation, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
		
		inline static void drawQuad(const glm::vec2 &position, float rotation, const Ref<SubTexture2D> &subtexture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, subtexture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const Ref<SubTexture2D> &subtexture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
	private:
		static void _drawQuad(const glm::vec3 &position, float rotation, const Ref<Texture2D> &texture, const glm::vec2 *texCoords, const glm::vec2 &tilingFactor, const glm::vec4 &color);

	public:
		// Non-rotated scaled quad
		inline static void drawQuad(const glm::vec2 &position, const glm::vec2 &scale, const glm::vec4 &color)
		{ drawQuad(glm::vec3(position, 0.0f), scale, color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const glm::vec4 &color);
		
		inline static void drawQuad(const glm::vec2 &position, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), scale, texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
		
		inline static void drawQuad(const glm::vec2 &position, const glm::vec2 &scale, const Ref<SubTexture2D> &subtexture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), scale, subtexture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const Ref<SubTexture2D> &subtexture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
	private:
		static void _drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 *texCoords, const glm::vec2 &tilingFactor, const glm::vec4 &color);

	public:
		// Rotated scaled quad
		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color)
		{ drawQuad(glm::vec3(position, 0.0f), rotation, scale, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color);
		
		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, scale, texture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));

		inline static void drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const Ref<SubTexture2D> &subtexture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f))
		{ drawQuad(glm::vec3(position, 0.0f), rotation, scale, subtexture, tilingFactor, color); }
		static void drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const Ref<SubTexture2D> &subtexture, const glm::vec2 &tilingFactor = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
	private:
		static void _drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 *texCoords, const glm::vec2 &tilingFactor, const glm::vec4 &color);
	};
}
