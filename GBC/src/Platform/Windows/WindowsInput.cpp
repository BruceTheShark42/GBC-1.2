#pragma once

#include "gbcpch.h"
#include "GBC/Core/Input.h"
#include "GBC/Core/Application.h"
#include <GLFW/glfw3.h>

namespace gbc
{
	bool Input::isKeyPressed(KeyCode keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		return glfwGetKey(window, static_cast<int>(keyCode)) == GLFW_PRESS;
	}

	bool Input::isKeyReleased(KeyCode keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		return glfwGetKey(window, static_cast<int>(keyCode)) == GLFW_RELEASE;
	}

	bool Input::isMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
	}

	bool Input::isMouseButtonReleased(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_RELEASE;
	}

	std::pair<float, float> Input::getMousePos()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	float Input::getMousePosX()
	{
		return getMousePos().first;
	}

	float Input::getMousePosY()
	{
		return getMousePos().second;
	}
}
