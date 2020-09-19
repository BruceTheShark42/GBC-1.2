#include "gbcpch.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

#include "GBC/Core/core.h"

#include "GBC/Events/KeyEvent.h"
#include "GBC/Events/MiscEvent.h"
#include "GBC/Events/MouseEvent.h"
#include "GBC/Events/WindowEvent.h"
#include "GBC/Events/DeviceEvent.h"

#include "GBC/Core/keyCodes.h"
#include "GBC/Core/mouseButtons.h"
#include "Platform/OpenGL/OpenGLContext.h"

// TODO: The only reason why this is here is because I needed a way
// to access the window handle from within glfw callbacks that don't
// pass it due to the callbacks being for joysticks and monitors.
// I needed access to the eventCallback so the rest of the engine
// has access to the event.
// If there is a better way to do this, I'm all ears.
#include "GBC/Core/Application.h"

namespace gbc
{
	Scope<Window> Window::create(const WindowProps& props)
	{
		return createScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		GBC_CORE_INFO("Creating Window - width={0} height={1} title={2} vsync={3} captureMouse={4} resizable={5} fullscreen={6} adaptiveSize={7}", props.width, props.height, props.title, props.vsync, props.captureMouse, props.resizable, props.fullscreen, props.adaptiveSize);

		state.title = props.title;
		state.current.width = props.width;
		state.current.height = props.height;
		state.resizable = props.resizable;
		state.fullscreen = props.fullscreen;
		state.adaptiveSize = props.adaptiveSize;

		static bool glfwInitialized = false;
		if (!glfwInitialized)
		{
			int success = glfwInit();
			GBC_CORE_ASSERT(success, "Couldn't initialize GLFW!");
			glfwSetErrorCallback([](int error, const char* description)
			{
				GBC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
			});
			glfwInitialized = true;
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
			auto [width, height] = getFullscreenSize(videoMode);
			state.current.width = width;
			state.current.height = height;
		}

		window = glfwCreateWindow(state.current.width, state.current.height, state.title, state.fullscreen ? primaryMonitor : nullptr, nullptr);
		GBC_CORE_ASSERT(window != nullptr, "Unable to create window!");

		// Set the window's position
		glfwSetWindowPos(window, state.current.x, state.current.y);

		context = new OpenGLContext(window);
		context->init();

		setVSync(props.vsync);
		setCaptureMouse(props.captureMouse);

		// Important things
		glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		
		// To access data in a callback, use user pointers
		glfwSetWindowUserPointer(window, &state);

		// Set callbacks
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(WindowCloseEvent());
		});
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.current.width = width;
			state.current.height = height;
			state.eventCallback(WindowResizeEvent(width, height));
		});
		glfwSetWindowPosCallback(window, [](GLFWwindow* window, int x, int y)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.current.x = x;
			state.current.y = y;
			state.eventCallback(WindowMoveEvent(x, y));
		});
		glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(WindowFocusEvent(focused == GLFW_TRUE));
		});
		glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(WindowMinimizeEvent(iconified == GLFW_TRUE));
		});
		glfwSetWindowMaximizeCallback(window, [](GLFWwindow* window, int maximized)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(WindowMaximizeEvent(maximized == GLFW_TRUE));
		});
		glfwSetKeyCallback(window, [](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			if (keyCode != GLFW_KEY_UNKNOWN)
			{
				switch (action)
				{
					case GLFW_PRESS: state.eventCallback(KeyPressEvent(static_cast<KeyCode>(keyCode), false)); break;
					case GLFW_REPEAT: state.eventCallback(KeyPressEvent(static_cast<KeyCode>(keyCode), true)); break;
					case GLFW_RELEASE: state.eventCallback(KeyReleaseEvent(static_cast<KeyCode>(keyCode))); break;
				}
			}
		});
		// GLFW has a bug where this doesn't get called when ctrl is pressed
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(KeyCharEvent(codepoint));
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			if (action == GLFW_PRESS)
				state.eventCallback(MouseButtonPressEvent(static_cast<MouseCode>(button)));
			else
				state.eventCallback(MouseButtonReleaseEvent(static_cast<MouseCode>(button)));
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(MouseMoveEvent((float)x, (float)y));
		});
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOff, double yOff)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(MouseScrollEvent((float)xOff, (float)yOff));
		});
		glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int entered)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(MouseEnterEvent(entered == GLFW_TRUE));
		});
		
		// The following callbacks I have not used before but I would like to account for every callback
		
		// This is CharCallback but better in every way, so use this instead
		// GLFW has a bug where this doesn't get called when ctrl is pressed
		glfwSetCharModsCallback(window, [](GLFWwindow* window, unsigned int codepoint, int mods)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(KeyCharModsEvent(codepoint, mods));
		});

		// This is where you drag and drop a file or multiple files onto the window
		glfwSetDropCallback(window, [](GLFWwindow* window, int pathCount, const char** paths)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(PathDropEvent(pathCount, paths));
		});

		// https://stackoverflow.com/questions/44719635/what-is-the-difference-between-glfwgetwindowsize-and-glfwgetframebuffersize/44720010
		// http://forum.lwjgl.org/index.php?topic=5976.0
		// From reading online about this, I think it's for high resolution displays
		// where a pixel on the screen is not necessarily one-to-one with the screen resolution.
		// tldr there can be half pixels
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(WindowFramebufferResizeEvent(width, height));
		});

		// This is when a joystick is connected or disconnected
		// See GLFWjoystickfun for more info
		// For reference, there is glfwSetJoystickUserPointer
		glfwSetJoystickCallback([](int jid, int event)
		{
			// Big brain hacks
			auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));

			state.eventCallback(DeviceJoystickConnectEvent(event == GLFW_CONNECTED, jid));
		});

		// This is the same as glfwSetJoystickCallback except for monitors
		// The monitor part likely will be difficult to abstract
		// There's also glfwSetMonitorUserPointer
		glfwSetMonitorCallback([](GLFWmonitor* monitor, int event)
		{
			// Big brain hacks
			auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));

			state.eventCallback(DeviceMonitorConnectEvent(event == GLFW_CONNECTED, monitor));
		});

		// I think this is called when the dpi thing is changed for the window
		glfwSetWindowContentScaleCallback(window, [](GLFWwindow* window, float scaleX, float scaleY)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(WindowContentScaleEvent(scaleX, scaleY));
		});

		// I think it's called when the window needs to refresh it's contents
		// it happens whenever pixels are "added"...
		//		during a window move
		//		 -- only if the window is partially off all monitors
		//		during a window resize that enlarges the window
		glfwSetWindowRefreshCallback(window, [](GLFWwindow* window)
		{
			auto& state = *static_cast<WindowState*>(glfwGetWindowUserPointer(window));
			state.eventCallback(WindowRefreshEvent());
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
		GBC_CORE_INFO("Window Set title={0}", state.title);
	}

	void WindowsWindow::setVSync(bool vsync)
	{
		glfwSwapInterval((int)vsync);
		state.vsync = vsync;
		GBC_CORE_INFO("Window Set vsync={0}", state.vsync);
	}

	void WindowsWindow::setCaptureMouse(bool captureMouse)
	{
		if (state.captureMouse != captureMouse)
		{
			glfwSetInputMode(window, GLFW_CURSOR, captureMouse ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
			state.captureMouse = captureMouse;
			GBC_CORE_INFO("Window Set cursorEnabled={0}", state.captureMouse);
		}
	}

	void WindowsWindow::setResizable(bool resizable)
	{
		if (state.resizable != resizable)
		{
			glfwSetWindowAttrib(window, GLFW_RESIZABLE, (int)resizable);
			state.resizable = resizable;
			GBC_CORE_INFO("Window Set resizable={0}", state.resizable);
		}
	}

	void WindowsWindow::setFullscreen(bool fullscreen)
	{
		if (fullscreen)
		{
			// Can change videomode while fullscreen
			// Only cache this the first time
			if (!state.fullscreen)
				saveDimensions();

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

			// https://stackoverflow.com/questions/21421074/how-to-create-a-full-screen-window-on-the-current-monitor-with-glfw
			// Get the monitor that most of the window is on
			int largestOverlap = INT_MIN;
			GLFWmonitor* monitor = nullptr;

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
			auto [width, height] = getFullscreenSize(videoMode);
			glfwSetWindowMonitor(window, monitor, 0, 0, width, height, GLFW_DONT_CARE);

			// Another GLFW bug? vsync state not saved when changing monitors
			// probably not a bug and im just not understanding the documentation,
			// but I don't like it
			setVSync(getVSync());
		}
		else
			glfwSetWindowMonitor(window, nullptr, state.preFullscreen.x, state.preFullscreen.y, state.preFullscreen.width, state.preFullscreen.height, GLFW_DONT_CARE);

		state.fullscreen = fullscreen;
		GBC_CORE_INFO("Window Set fullscreen={0}", state.fullscreen);
	}

	std::pair<int, int> WindowsWindow::getFullscreenSize(const GLFWvidmode* videoMode) const
	{
		if (state.adaptiveSize) return { videoMode->width, videoMode->height };
		return { state.current.width, state.current.height };
	}

	void WindowsWindow::saveDimensions()
	{
		state.preFullscreen.x = state.current.x;
		state.preFullscreen.y = state.current.y;
		state.preFullscreen.width = state.current.width;
		state.preFullscreen.height = state.current.height;
	}
}
