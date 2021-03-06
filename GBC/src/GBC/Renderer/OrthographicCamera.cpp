#include "gbcpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace gbc
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view(1.0f), projectionView(projection * view), 
		position(0.0f, 0.0f, 0.0f), rotation(0.0f) {}

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
	{
		projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		projectionView = projection * view;
	}

	void OrthographicCamera::calculate()
	{
		view = glm::inverse(glm::rotate(glm::translate(glm::mat4(1.0f), position), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }));
		projectionView = projection * view;
	}
}
