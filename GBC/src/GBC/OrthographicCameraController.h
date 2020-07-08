#pragma once

#include "GBC/Renderer/Camera.h"
#include "GBC/Core/TimeStep.h"
#include "GBC/Events/KeyEvent.h"
#include "GBC/Events/MouseEvent.h"
#include "GBC/Events/WindowEvent.h"
#include <glm/glm.hpp>

namespace gbc
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, float zoomLevel = 1.0f, const glm::vec3 &position = { 0.0f, 0.0f, 0.0f }, float rotation = 0.0f);

		void onUpdate(TimeStep ts);
		void onEvent(Event &e);

		void resize(float width, float height);

		inline const OrthographicCamera& getCamera() const { return camera; }

		void setZoomLevel(float zoomLevel);
	private:
		void calculate();

		bool onMouseScrolled(MouseScrolledEvent &e);
		bool onWindowResized(WindowResizedEvent &e);
	private:
		float aspectRatio;
		float zoomLevel, zoomSpeed;

		OrthographicCamera camera;
		glm::vec3 position;
		float movementSpeed;
		float rotation, rotationSpeed;
	};
}
