#include "gbcpch.h"
#include "OrthographicCameraController.h"
#include "GBC/Core/Input.h"
#include "GBC/Core/keyCodes.h"

namespace gbc
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float zoomLevel, const glm::vec3& position, float rotation)
		: aspectRatio(aspectRatio), zoomLevel(zoomLevel), zoomSpeed(0.5f),
		camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel),
		position(position), rotation(rotation), movementSpeed(5.0f), rotationSpeed(180.0f) {}

	void OrthographicCameraController::onUpdate(TimeStep ts)
	{
		if (Input::isKeyPressed(KeyCode::W))
		{
			position.y += movementSpeed * cos(glm::radians(rotation)) * ts;
			position.x -= movementSpeed * sin(glm::radians(rotation)) * ts;
		}
		if (Input::isKeyPressed(KeyCode::S))
		{
			position.y -= movementSpeed * cos(glm::radians(rotation)) * ts;
			position.x += movementSpeed * sin(glm::radians(rotation)) * ts;
		}
		if (Input::isKeyPressed(KeyCode::A))
		{
			position.x -= movementSpeed * cos(glm::radians(rotation)) * ts;
			position.y -= movementSpeed * sin(glm::radians(rotation)) * ts;
		}
		if (Input::isKeyPressed(KeyCode::D))
		{
			position.x += movementSpeed * cos(glm::radians(rotation)) * ts;
			position.y += movementSpeed * sin(glm::radians(rotation)) * ts;
		}
		
		if (Input::isKeyPressed(KeyCode::Left))
			rotation += rotationSpeed * ts;
		if (Input::isKeyPressed(KeyCode::Right))
			rotation -= rotationSpeed * ts;

		camera.setPosition(position);
		camera.setRotation(rotation);
	}

	void OrthographicCameraController::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrollEvent>(GBC_BIND_FUNC(OrthographicCameraController::onMouseScroll));
		dispatcher.dispatch<WindowResizeEvent>(GBC_BIND_FUNC(OrthographicCameraController::onWindowResize));
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

	bool OrthographicCameraController::onMouseScroll(MouseScrollEvent& e)
	{
		zoomLevel -= e.getY() * zoomSpeed;
		if (zoomLevel < zoomSpeed)
			zoomLevel = zoomSpeed;
		calculate();
		return false;
	}

	bool OrthographicCameraController::onWindowResize(WindowResizeEvent& e)
	{
		resize((float)e.getWidth(), (float)e.getHeight());
		return false;
	}
}
