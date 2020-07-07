#pragma once

#include <glm/glm.hpp>

#include "GBC/Renderer/Texture.h"

namespace gbc
{
	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D> &texture, const glm::vec2 &min, const glm::vec2 &max);

		static Ref<SubTexture2D> createFromCoords(const Ref<Texture2D> &texture, const glm::vec2 &cellSize, const glm::vec2 &coords, const glm::vec2 &size = { 1.0f, 1.0f });

		inline const Ref<Texture2D> getTexture() const { return texture; }
		inline const glm::vec2* getTextureCoords() const { return texCoords; }
	private:
		Ref<Texture2D> texture;
		glm::vec2 texCoords[4];
	};
}
