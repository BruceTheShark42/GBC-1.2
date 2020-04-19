#pragma once

#include "gbcpch.h"
#include "Platform/Windows/WindowsInput.h"
#include <GLFW/glfw3.h>
#include "GBC/Application.h"

namespace gbc
{
	Input *Input::instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		return glfwGetKey(window, keyCode) != GLFW_RELEASE;
	}

	bool WindowsInput::isKeyReleasedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		return glfwGetKey(window, keyCode) == GLFW_RELEASE;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		return glfwGetMouseButton(window, button) == GLFW_PRESS;
	}

	bool WindowsInput::isMouseButtonReleasedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		return glfwGetMouseButton(window, button) == GLFW_RELEASE;
	}

	std::pair<float, float> WindowsInput::getMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	float WindowsInput::getMousePosXImpl()
	{
		auto [x, y] = getMousePos();
		return x;
	}

	float WindowsInput::getMousePosYImpl()
	{
		auto [x, y] = getMousePos();
		return y;
	}
}
