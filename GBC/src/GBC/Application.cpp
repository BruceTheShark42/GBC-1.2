#include "gbcpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace gbc
{
	Application *Application::instance = nullptr;

	Application::Application()
		: running(true), lastFrameTime(0.0f)
	{
		GBC_CORE_ASSERT(instance == nullptr, "Attempted to recreate Application!");
		instance = this;

		window = Scope<Window>(Window::create());
		window->setEventCallback(GBC_BIND_FUNC(Application::onEvent));

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
			float time = (float)glfwGetTime();
			TimeStep ts = time - lastFrameTime;
			lastFrameTime = time;

			layerStack.onUpdate(ts);

#ifdef GBC_ENABLE_IMGUI
			imguiLayer->begin();
			layerStack.onImGuiRender();
			imguiLayer->end();
#endif

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
