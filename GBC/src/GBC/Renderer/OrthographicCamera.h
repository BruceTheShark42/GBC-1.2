#pragma once

#include <glm/glm.hpp>

namespace gbc
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f);
		void setProjection(float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f);

		inline const glm::vec3& getPosition() const { return position; }
		inline void setPosition(const glm::vec3& position) { this->position = position; calculate(); }

		inline float getRotation() const { return rotation; }
		inline void setRotation(float rotation) { this->rotation = rotation; calculate(); }

		inline const glm::mat4& getView() const { return view; }
		inline const glm::mat4& getProjection() const { return projection; }
		inline const glm::mat4& getProjectionView() const { return projectionView; }
	private:
		void calculate();

		glm::mat4 view, projection, projectionView;
		glm::vec3 position;
		float rotation;
	};
}
