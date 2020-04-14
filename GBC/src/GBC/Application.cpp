#include "gbcpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace gbc
{
	Application::Application()
		: running(true)
	{
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(GBC_BIND_FUNC(Application::onEvent));
	}

	Application::~Application()
	{

	}

	void Application::onEvent(Event &e)
	{
		GBC_CORE_TRACE(e);

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClosedEvent>(GBC_BIND_FUNC(Application::onWindowClosedEvent));
	}

	bool Application::onWindowClosedEvent(WindowClosedEvent &e)
	{
		running = false;
		return true;
	}

	void Application::run()
	{
		while (running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			window->onUpdate();
		}
	}
}
