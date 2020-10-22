#pragma once

#include  "GBC/Renderer/Camera.h"

namespace gbc
{
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };

		SceneCamera();
		virtual ~SceneCamera() = default;
		void setViewportSize(int width, int height);

		void setPerspective(float fov, float nearClip, float farClip);
		inline float getPerspectiveFOV() const { return perspectiveFOV; }
		inline void setPerspectiveFOV(float fov) { perspectiveFOV = fov; recalculateProjection(); }
		inline float getPerspectiveNearClip() const { return perspectiveNear; }
		inline void setPerspectiveNearClip(float nearClip) { perspectiveNear = nearClip; recalculateProjection(); }
		inline float getPerspectiveFarClip() const { return perspectiveFar; }
		inline void setPerspectiveFarClip(float farClip) { perspectiveFar = farClip; recalculateProjection(); }

		void setOrthographic(float size, float nearClip, float farClip);
		inline float getOrthographicSize() const { return orthographicSize; }
		inline void setOrthographicSize(float size) { orthographicSize = size; recalculateProjection(); }
		inline float getOrthographicNearClip() const { return orthographicNear; }
		inline void setOrthographicNearClip(float nearClip) { orthographicNear = nearClip; recalculateProjection(); }
		inline float getOrthographicFarClip() const { return orthographicFar; }
		inline void setOrthographicFarClip(float farClip) { orthographicFar = farClip; recalculateProjection(); }

		inline ProjectionType getProjectionType() const { return projectionType; }
		inline void setProjectionType(ProjectionType type) { projectionType = type; recalculateProjection(); }
	private:
		void recalculateProjection();

		ProjectionType projectionType = ProjectionType::Perspective;

		// Perspective stuff
		float perspectiveFOV = glm::radians(90.0f);
		float perspectiveNear = 0.001f;
		float perspectiveFar = 1000.0f;

		// Orthographic stuff
		float orthographicSize = 10.0f;
		float orthographicNear = -1.0f;
		float orthographicFar = 1.0f;

		// Other stuff
		float aspectRatio = 0.0f;
	};

}
