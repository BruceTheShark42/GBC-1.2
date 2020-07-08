#pragma once

#include "gbcpch.h"
#include "GBC/Core/Input.h"
#include "GBC/Core/Application.h"
#include <GLFW/glfw3.h>

namespace gbc
{
	bool Input::isKeyPressed(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		return glfwGetKey(window, keyCode) != GLFW_RELEASE;
	}

	bool Input::isKeyReleased(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		return glfwGetKey(window, keyCode) == GLFW_RELEASE;
	}

	bool Input::isMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		return glfwGetMouseButton(window, button) == GLFW_PRESS;
	}

	bool Input::isMouseButtonReleased(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		return glfwGetMouseButton(window, button) == GLFW_RELEASE;
	}

	std::pair<float, float> Input::getMousePos()
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	float Input::getMousePosX()
	{
		auto [x, y] = getMousePos();
		return x;
	}

	float Input::getMousePosY()
	{
		auto [x, y] = getMousePos();
		return y;
	}
}
