#include "gbcpch.h"
#include "Application.h"
#include "GBC/Renderer/Renderer.h"
#include <GLFW/glfw3.h>

namespace gbc
{
	Application *Application::instance = nullptr;

	Application::Application()
		: running(true), minimized(false), lastFrameTime(0.0f)
	{
		GBC_CORE_ASSERT(instance == nullptr, "Attempted to recreate Application!");
		instance = this;

		window = Scope<Window>(Window::create());
		window->setEventCallback(GBC_BIND_FUNC(Application::onEvent));

		Renderer::init();

#ifdef GBC_ENABLE_IMGUI
		imguiLayer = new ImGuiLayer();
		layerStack.pushOverlay(imguiLayer);
#endif
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
			dispatcher.dispatch<WindowClosedEvent>(GBC_BIND_FUNC(Application::onWindowClosed));
			dispatcher.dispatch<WindowResizedEvent>(GBC_BIND_FUNC(Application::onWindowResized));
		}
	}

	void Application::run()
	{
		while (running)
		{
			float time = (float)glfwGetTime();
			TimeStep ts = time - lastFrameTime;
			lastFrameTime = time;

			if (!minimized)
				layerStack.onUpdate(ts);

#ifdef GBC_ENABLE_IMGUI
				imguiLayer->begin();
				layerStack.onImGuiRender();
				imguiLayer->end();
#endif

			window->onUpdate();
		}
	}

	bool Application::onWindowClosed(WindowClosedEvent &e)
	{
		running = false;
		return true;
	}

	bool Application::onWindowResized(WindowResizedEvent &e)
	{
		if (e.getWidth() == 0 || e.getHeight() == 0)
		{
			minimized = true;
			return false;
		}

		minimized = false;
		Renderer::onWindowResized(e.getWidth(), e.getHeight());
		return false;
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
