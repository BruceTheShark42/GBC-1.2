#include "gbcpch.h"
#include "WindowsWindow.h"
#include "GBC/Core/core.h"
#include "GBC/Events/KeyEvent.h"
#include "GBC/Events/MouseEvent.h"
#include "GBC/Events/WindowEvent.h"
#include "GBC/Core/keyCodes.h"
#include "GBC/Core/mouseButtons.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace gbc
{
	static bool GLFWinitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		GBC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::create(const WindowProps& props)
	{
		return createScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		GBC_CORE_INFO("Creating Window - title=\"{0}\" width={1} height={2} resizable={3} fullscreen={4} vSync={5} cursorEnabled={6}", props.title, props.width, props.height, props.resizable, props.fullscreen, props.vsync, props.captureMouse);

		state.title = props.title;
		state.current.width = props.width;
		state.current.height = props.height;
		state.resizable = props.resizable;
		state.fullscreen = props.fullscreen;

		if (!GLFWinitialized)
		{
			int success = glfwInit();
			GBC_CORE_ASSERT(success, "Couldn't initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWinitialized = true;
		}

		// Set GLFW window hints
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, state.resizable);

		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

		// Calculate the offset needed for the window to be centered in the primary monitor
		state.current.x = (videoMode->width - state.current.width) / 2;
		state.current.y = (videoMode->height - state.current.height) / 2;

		if (state.fullscreen)
		{
			saveDimensions();
			state.current.x = 0;
			state.current.y = 0;
		}

		window = glfwCreateWindow(state.current.width, state.current.height, state.title, state.fullscreen ? primaryMonitor : nullptr, nullptr);
		GBC_CORE_ASSERT(window != nullptr, "Unable to create window!");

		// Set the window's position
		glfwSetWindowPos(window, state.current.x, state.current.y);

		context = new OpenGLContext(window);
		context->init();

		setVSync(props.vsync);
		setCaptureMouse(props.captureMouse);
		
		// To access data in a callback, use user pointers
		glfwSetWindowUserPointer(window, &state);

		// Set callbacks
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.callback(WindowClosedEvent());
		});
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.current.width = width;
			state.current.height = height;
			state.callback(WindowResizedEvent(width, height));
		});
		glfwSetWindowPosCallback(window, [](GLFWwindow* window, int x, int y)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.current.x = x;
			state.current.y = y;
			state.callback(WindowMovedEvent(x, y));
		});
		glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			if (focused == GLFW_TRUE)
				state.callback(WindowGainedFocusEvent());
			else
				state.callback(WindowLostFocusEvent());
		});
		glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			if (iconified == GLFW_TRUE)
				state.callback(WindowMinimizedEvent());
			else
				state.callback(WindowUnminimizedEvent());
		});
		glfwSetWindowMaximizeCallback(window, [](GLFWwindow* window, int maximized)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			if (maximized == GLFW_TRUE)
				state.callback(WindowMaximizedEvent());
			else
				state.callback(WindowUnmaximizedEvent());
		});
		glfwSetKeyCallback(window, [](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			if (keyCode != GLFW_KEY_UNKNOWN)
			{
				switch (action)
				{
					case GLFW_PRESS:
						state.callback(KeyPressedEvent(static_cast<KeyCode>(keyCode), false));
						break;
					case GLFW_REPEAT:
						state.callback(KeyPressedEvent(static_cast<KeyCode>(keyCode), true));
						break;
					case GLFW_RELEASE:
						state.callback(KeyReleasedEvent(static_cast<KeyCode>(keyCode)));
						break;
				}
			}
		});
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int charCode)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.callback(KeyTypedEvent(charCode));
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			if (action == GLFW_PRESS)
				state.callback(MouseButtonPressedEvent(static_cast<MouseCode>(button)));
			else
				state.callback(MouseButtonReleasedEvent(static_cast<MouseCode>(button)));
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.callback(MouseMovedEvent((float)x, (float)y));
		});
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOff, double yOff)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.callback(MouseScrolledEvent((float)xOff, (float)yOff));
		});
		glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int entered)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			if (entered == GLFW_TRUE)
				state.callback(MouseEnteredEvent());
			else
				state.callback(MouseExitedEvent());
		});
		
		// The following callbacks I have not used before but I would like to account for every callback
		// TODO: implement events for each one of these
		// TODO: Merge GBC-1.2's shaders with GB4's

		// This is CharCallback but better in every way, so use this instead
		glfwSetCharModsCallback(window, [](GLFWwindow* window, unsigned int codepoint, int mods)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			GBC_CORE_DEBUG("Char Mod Event - Codepoint={0} Mods={1}", codepoint, mods);
		});

		// This is where you drag and drop a file or multiple files onto the window
		glfwSetDropCallback(window, [](GLFWwindow* window, int pathCount, const char** paths)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			GBC_CORE_DEBUG("Path Drop Event - PathCount={0} FirstPath={1}", pathCount, paths[0]);
		});

		// https://stackoverflow.com/questions/44719635/what-is-the-difference-between-glfwgetwindowsize-and-glfwgetframebuffersize/44720010
		// http://forum.lwjgl.org/index.php?topic=5976.0
		// From reading online about this, I think it's for high resolution displays
		// where a pixel on the screen is not necessarily one-to-one with the screen resolution.
		// tldr there can be half pixels
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			GBC_CORE_DEBUG("Framebuffer Resize Event - Width={0} Height={1}", width, height);
		});

		// This is when a joystick is connected or disconnected
		// See GLFWjoystickfun for more info
		// For reference, there is glfwSetJoystickUserPointer
		glfwSetJoystickCallback([](int id, int event)
		{
			GBC_CORE_DEBUG("Joystick Event - ID={0}, Connected={1}", id, event == GLFW_CONNECTED);
		});

		// This is the same as glfwSetJoystickCallback except for monitors
		// The monitor part likely will be difficult to abstract
		// There's also glfwSetMonitorUserPointer
		glfwSetMonitorCallback([](GLFWmonitor* monitor, int event)
		{
			GBC_CORE_DEBUG("Monitor Event - Connected={0}", event == GLFW_CONNECTED);
		});

		// I think this is called when the dpi thing is changed for the window
		glfwSetWindowContentScaleCallback(window, [](GLFWwindow* window, float xScale, float yScale)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			GBC_CORE_DEBUG("Window Content Scale Event - XScale={0} YScale={1}", xScale, yScale);
		});

		// I think it's called when the window needs to refresh it's contents
		// it happens whenever pixels are "added"...
		//		during a window move
		//		 -- only if the window is partially off all monitors
		//		during a window resize that enlarges the window
		glfwSetWindowRefreshCallback(window, [](GLFWwindow* window)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			GBC_CORE_DEBUG("Window Refresh Event");
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

	float WindowsWindow::getElapsedTime() const
	{
		float time = (float)glfwGetTime();
		float elapsedTime = time - lastTime;
		lastTime = time;
		return elapsedTime;
	}

	void WindowsWindow::setTitle(const char* title)
	{
		glfwSetWindowTitle(window, title);
		state.title = title;
	}

	void WindowsWindow::setVSync(bool vsync)
	{
		GBC_CORE_INFO("Window Set vsync={0}", state.vsync);
		glfwSwapInterval((int)vsync);
		state.vsync = vsync;
	}

	void WindowsWindow::setCaptureMouse(bool captureMouse)
	{
		if (state.captureMouse != captureMouse)
		{
			GBC_CORE_INFO("Window Set cursorEnabled={0}", state.captureMouse);
			glfwSetInputMode(window, GLFW_CURSOR, captureMouse ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
			state.captureMouse = captureMouse;
		}
	}

	void WindowsWindow::setResizable(bool resizable)
	{
		if (state.resizable != resizable)
		{
			GBC_CORE_INFO("Window Set resizable={0}", state.resizable);
			glfwSetWindowAttrib(window, GLFW_RESIZABLE, (int)resizable);
			state.resizable = resizable;
		}
	}

	void WindowsWindow::setFullscreen(bool fullscreen)
	{
		if (state.fullscreen != fullscreen)
		{
			GBC_CORE_INFO("Window Set fullscreen={0}", state.fullscreen);

			// TODO: should query refresh rate from wherever it is
			int refreshRate = state.vsync ? 60 : 0;

			if (fullscreen)
			{
				saveDimensions();

				// https://stackoverflow.com/questions/21421074/how-to-create-a-full-screen-window-on-the-current-monitor-with-glfw
				// Get the monitor that most of the window is on
				int largestOverlap = INT_MIN;
				GLFWmonitor* monitor = nullptr;

				// Okay, so I've encountered what I believe to be a bug in GLFW.
				// If I run this application, I can enable and disable fullscreen
				// perfectly fine on my primary monitor, but when I plug in another
				// monitor, it's as if the primary monitor's pointer becomes invalid
				// somehow? When I enable fullscreen on the primary monitor, the
				// window dissappears, and comes back normally when I disable
				// fullscreen. I have checked and the pointers have the same values
				// while the monitors are connected, as is to be expected. But even
				// with the same pointer, enabling fullscreen on the primary monitor
				// before the second monitor is connected is fine, and when the second
				// one is connected, enabling fullscreen on the primary monitor craps out.
				int monitorCount;
				GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

				for (int i = 0; i < monitorCount; i++)
				{
					//GB4_LOG_WARN("{0}", (void*)monitors[i]);
					const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[i]);
					
					int monitorX, monitorY;
					glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);

					int overlapX = std::max(0, std::min(state.current.x + state.current.width, monitorX + videoMode->width) - std::max(state.current.x, monitorX));
					int overlapY = std::max(0, std::min(state.current.y + state.current.height, monitorY + videoMode->height) - std::max(state.current.y, monitorY));
					int overlap = overlapX * overlapY;

					if (overlap > largestOverlap)
					{
						largestOverlap = overlap;
						monitor = monitors[i];
					}
				}

				const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
				glfwSetWindowMonitor(window, monitor, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);
			}
			else
				glfwSetWindowMonitor(window, nullptr, state.previous.x, state.previous.x, state.previous.width, state.previous.height, GLFW_DONT_CARE);

			setVSync(getVSync());

			state.fullscreen = fullscreen;
		}
	}

	void WindowsWindow::saveDimensions()
	{
		state.previous.x = state.current.x;
		state.previous.y = state.current.y;
		state.previous.width = state.current.width;
		state.previous.height = state.current.height;
	}
}
