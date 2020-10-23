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
		projectionType = ProjectionType::Orthographic;
		orthographicSize = size;
		orthographicNear = nearClip;
		orthographicFar = farClip;
		recalculateProjection();
	}

	void SceneCamera::setPerspective(float fov, float nearClip, float farClip)
	{
		projectionType = ProjectionType::Perspective;
		perspectiveFOV = fov;
		perspectiveNear = nearClip;
		perspectiveFar = farClip;
		recalculateProjection();
	}

	void SceneCamera::setViewportSize(int width, int height)
	{
		aspectRatio = (float)width / (float)height;
		// minimizing/alt-tabbing in fullscreen cause the
		// height to be zero and dividing by zero is bad
		if (height != 0.0f)
			recalculateProjection();
	}

	void SceneCamera::recalculateProjection()
	{
		switch (projectionType)
		{
			case gbc::SceneCamera::ProjectionType::Perspective:
			{
				projection = glm::perspective(perspectiveFOV, aspectRatio, perspectiveNear, perspectiveFar);
				break;
			}
			case gbc::SceneCamera::ProjectionType::Orthographic:
			{
				float orthoLeft = -orthographicSize * aspectRatio * 0.5f;
				float orthoRight = orthographicSize * aspectRatio * 0.5f;
				float orthoBottom = -orthographicSize * 0.5f;
				float orthoTop = orthographicSize * 0.5f;

				projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthographicNear, orthographicFar);
				break;
			}
		}
	}
}
