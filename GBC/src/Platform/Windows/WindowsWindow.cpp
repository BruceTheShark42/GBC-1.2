#include "gbcpch.h"
#include "WindowsWindow.h"
#include "GBC/core.h"
#include "GBC/Events/KeyEvent.h"
#include "GBC/Events/MouseEvent.h"
#include "GBC/Events/WindowEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace gbc
{
	static bool GLFWinitialized = false;

	static void GLFWErrorCallback(int error, const char *description)
	{
		GBC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::create(const WindowProps &props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps &props)
	{
		GBC_CORE_INFO("Creating Window - title = \"{0}\" | width = {1} | height = {2} | resizable = {3} | fullscreen = {4} | vSync = {5} | cursorEnabled = {6}", props.title, props.width, props.height, props.resizable, props.fullscreen, props.vsync, props.cursorEnabled);

		data.title = props.title;
		data.width = props.width;
		data.height = props.height;
		data.resizable = props.resizable;
		data.fullscreen = props.fullscreen;

		if (!GLFWinitialized)
		{
			int success = glfwInit();
			GBC_CORE_ASSERT(success, "Couldn't initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWinitialized = true;
		}

		// Set window hints
		glfwWindowHint(GLFW_RESIZABLE, data.resizable);

		monitor = glfwGetPrimaryMonitor();
		videoMode = glfwGetVideoMode(monitor);

		data.x = (videoMode->width - data.width) / 2;
		data.y = (videoMode->height - data.height) / 2;

		if (data.fullscreen)
		{
			data.pX = data.x;
			data.pY = data.y;
			data.pWidth = data.width;
			data.pHeight = data.height;
			data.x = 0;
			data.y = 0;
			data.width = videoMode->width;
			data.height = videoMode->height;
			window = glfwCreateWindow(data.width, data.height, data.title.c_str(), monitor, nullptr);
		}
		else
			window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);

		GBC_CORE_ASSERT(window != nullptr, "Unable to create window!");

		context = new OpenGLContext(window);
		context->init();

		glfwSetWindowUserPointer(window, &data);
		glfwSetWindowPos(window, data.x, data.y);
		glfwSetWindowUserPointer(window, &data);
		setVSync(props.vsync);
		setCursorEnabled(props.cursorEnabled);

		// Set callbacks
		glfwSetWindowCloseCallback(window, [](GLFWwindow *window)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.callback(WindowClosedEvent());
		});
		glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			data.callback(WindowResizedEvent(width, height));
		});
		glfwSetWindowPosCallback(window, [](GLFWwindow *window, int x, int y)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.x = x;
			data.y = y;
			data.callback(WindowMovedEvent(x, y));
		});
		glfwSetWindowFocusCallback(window, [](GLFWwindow *window, int focused)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (focused == GLFW_TRUE)
				data.callback(WindowGainedFocusEvent());
			else
				data.callback(WindowLostFocusEvent());
		});
		glfwSetWindowIconifyCallback(window, [](GLFWwindow *window, int iconified)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (iconified == GLFW_TRUE)
				data.callback(WindowMinimizedEvent());
			else
				data.callback(WindowUnminimizedEvent());
		});
		glfwSetWindowMaximizeCallback(window, [](GLFWwindow *window, int maximized)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (maximized == GLFW_TRUE)
				data.callback(WindowMaximizedEvent());
			else
				data.callback(WindowUnmaximizedEvent());
		});
		glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (key != GLFW_KEY_UNKNOWN)
			{
				switch (action)
				{
					case GLFW_PRESS:
						data.callback(KeyPressedEvent(key, false));
						break;
					case GLFW_REPEAT:
						data.callback(KeyPressedEvent(key, true));
						break;
					case GLFW_RELEASE:
						data.callback(KeyReleasedEvent(key));
						break;
				}
			}
		});
		glfwSetCharCallback(window, [](GLFWwindow *window, unsigned int keyCode)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.callback(KeyTypedEvent(keyCode));
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS)
				data.callback(MouseButtonPressedEvent(button));
			else
				data.callback(MouseButtonReleasedEvent(button));
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.callback(MouseMovedEvent((float)x, (float)y));
		});
		glfwSetScrollCallback(window, [](GLFWwindow *window, double xOff, double yOff)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.callback(MouseScrolledEvent((float)xOff, (float)yOff));
		});
		glfwSetCursorEnterCallback(window, [](GLFWwindow *window, int entered)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (entered == GLFW_TRUE)
				data.callback(MouseEnteredEvent());
			else
				data.callback(MouseExitedEvent());
		});

		glfwShowWindow(window);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		context->swapBuffers();
	}

	void WindowsWindow::setFullscreen(bool enabled)
	{
		if (data.fullscreen != enabled)
		{
			data.fullscreen = enabled;
			GBC_CORE_INFO("Window Set fullscreen={0}", data.fullscreen);
			if (enabled)
			{
				data.pX = data.x;
				data.pY = data.y;
				data.pWidth = data.width;
				data.pHeight = data.height;
				glfwSetWindowMonitor(window, monitor, 0, 0, videoMode->width, videoMode->height, 0);
			}
			else
				glfwSetWindowMonitor(window, 0, data.pX, data.pY, data.pWidth, data.pHeight, 0);
		}
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (data.vsync != enabled)
		{
			data.vsync = enabled;
			GBC_CORE_INFO("Window Set vSync={0}", data.vsync);
			glfwSwapInterval((int)enabled);
		}
	}

	void WindowsWindow::setCursorEnabled(bool enabled)
	{
		if (data.cursorEnabled != enabled)
		{
			data.cursorEnabled = enabled;
			GBC_CORE_INFO("Window Set cursorEnabled={0}", data.cursorEnabled);
			glfwSetInputMode(window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
		}
	}
}
