#include "gbcpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace gbc
{
	SceneCamera::SceneCamera()
	{
		recalculateProjection();
	}

	void SceneCamera::setOrthographic(float size, float nearClip, float farClip)
	{
		orthoSize = size;
		orthoNear = nearClip;
		orthoFar = farClip;
		recalculateProjection();
	}

	void SceneCamera::setViewportSize(int width, int height)
	{
		aspectRatio = (float)width / (float)height;
		recalculateProjection();
	}

	void SceneCamera::recalculateProjection()
	{
		float orthoLeft = -orthoSize * aspectRatio * 0.5f;
		float orthoRight = orthoSize * aspectRatio * 0.5f;
		float orthoBottom = -orthoSize * 0.5f;
		float orthoTop = orthoSize * 0.5f;

		projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoNear, orthoFar);
	}
}
