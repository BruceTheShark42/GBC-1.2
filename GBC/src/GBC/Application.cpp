#include "gbcpch.h"
#include "Application.h"
#include <glad/glad.h>
#include "Input.h"

namespace gbc
{
	Application *Application::instance = nullptr;

	Application::Application()
		: running(true)
	{
		GBC_CORE_ASSERT(instance == nullptr, "Attempted to recreate Application!");
		instance = this;

		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(GBC_BIND_FUNC(Application::onEvent));
	}

	Application::~Application()
	{

	}

	void Application::onEvent(Event &e)
	{
		GBC_CORE_TRACE(e);

		if (!layerStack.onEvent(e))
		{
			EventDispatcher dispatcher(e);
			dispatcher.dispatch<WindowClosedEvent>(GBC_BIND_FUNC(Application::onWindowClosedEvent));
		}
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

			layerStack.onUpdate();
			
			auto [x, y] = Input::getMousePos();
			GBC_CORE_INFO("({0}, {1})", x, y);

			window->onUpdate();
		}
	}

	void Application::pushLayer(Layer *layer)
	{
		layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer *overlay)
	{
		layerStack.pushOverlay(overlay);
	}
}
