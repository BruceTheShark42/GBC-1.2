#pragma once

#include <glm/glm.hpp>

namespace gbc
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: projection(projection) {}

		virtual ~Camera() = default;
	public:
		inline const glm::mat4& getProjection() const { return projection; }
	protected:
		glm::mat4 projection = glm::mat4(1.0f);
	};
}
