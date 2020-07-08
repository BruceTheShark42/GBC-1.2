#include "gbcpch.h"
#include "OrthographicCameraController.h"
#include "GBC/Core/Input.h"
#include "GBC/Core/keyCodes.h"

namespace gbc
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float zoomLevel, const glm::vec3 &position, float rotation)
		: aspectRatio(aspectRatio), zoomLevel(zoomLevel), zoomSpeed(0.5f),
		camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel),
		position(position), rotation(rotation), movementSpeed(5.0f), rotationSpeed(180.0f) {}

	void OrthographicCameraController::onUpdate(TimeStep ts)
	{
		if (Input::isKeyPressed(GBC_KEY_W))
		{
			position.y += movementSpeed * cos(glm::radians(rotation)) * ts;
			position.x -= movementSpeed * sin(glm::radians(rotation)) * ts;
		}
		if (Input::isKeyPressed(GBC_KEY_S))
		{
			position.y -= movementSpeed * cos(glm::radians(rotation)) * ts;
			position.x += movementSpeed * sin(glm::radians(rotation)) * ts;
		}
		if (Input::isKeyPressed(GBC_KEY_A))
		{
			position.x -= movementSpeed * cos(glm::radians(rotation)) * ts;
			position.y -= movementSpeed * sin(glm::radians(rotation)) * ts;
		}
		if (Input::isKeyPressed(GBC_KEY_D))
		{
			position.x += movementSpeed * cos(glm::radians(rotation)) * ts;
			position.y += movementSpeed * sin(glm::radians(rotation)) * ts;
		}
		
		if (Input::isKeyPressed(GBC_KEY_LEFT))
			rotation += rotationSpeed * ts;
		if (Input::isKeyPressed(GBC_KEY_RIGHT))
			rotation -= rotationSpeed * ts;

		camera.setPosition(position);
		camera.setRotation(rotation);
	}

	void OrthographicCameraController::onEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(GBC_BIND_FUNC(OrthographicCameraController::onMouseScrolled));
		dispatcher.dispatch<WindowResizedEvent>(GBC_BIND_FUNC(OrthographicCameraController::onWindowResized));
	}

	void OrthographicCameraController::resize(float width, float height)
	{
		aspectRatio = width / height;
		calculate();
	}

	void OrthographicCameraController::setZoomLevel(float zoomLevel)
	{
		this->zoomLevel = zoomLevel;
		calculate();
	}

	void OrthographicCameraController::calculate()
	{
		camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent &e)
	{
		zoomLevel -= e.getY() * zoomSpeed;
		if (zoomLevel < zoomSpeed)
			zoomLevel = zoomSpeed;
		calculate();
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizedEvent &e)
	{
		resize((float)e.getWidth(), (float)e.getHeight());
		return false;
	}
}
