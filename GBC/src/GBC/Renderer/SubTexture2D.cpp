#include "gbcpch.h"
#include "SubTexture2D.h"

namespace gbc
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D> &texture, const glm::vec2 &min, const glm::vec2 &max)
		: texture(texture)
	{
		texCoords[0] = { min.x, min.y };
		texCoords[1] = { max.x, min.y };
		texCoords[2] = { max.x, max.y };
		texCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::createFromCoords(const Ref<Texture2D> &texture, const glm::vec2 &cellSize, const glm::vec2 &coords, const glm::vec2 &size)
	{
		glm::vec2 min = { coords.x * cellSize.x / texture->getWidth(), coords.y * cellSize.y / texture->getHeight() };
		glm::vec2 max = { (coords.x + size.x) * cellSize.x / texture->getWidth(), (coords.y + size.y) * cellSize.y / texture->getHeight() };
		return gbc::createRef<SubTexture2D>(texture, min, max);
	}
}
