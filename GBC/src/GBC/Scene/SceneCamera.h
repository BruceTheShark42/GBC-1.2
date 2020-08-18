#pragma once

#include  "GBC/Renderer/Camera.h"

namespace gbc
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;
	public:
		void setOrthographic(float size, float nearClip, float farClip);
		void setViewportSize(unsigned int width, unsigned int height);
	private:
		void recalculateProjection();
	private:
		float orthoSize = 10.0f;
		float orthoNear = -1.0f, orthoFar = 1.0f;
		float aspectRatio = 0.0f;
	};

}
