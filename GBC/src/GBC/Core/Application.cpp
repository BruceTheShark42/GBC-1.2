#include "gbcpch.h"
#include "Application.h"
#include "GBC/Renderer/Renderer.h"

namespace gbc
{
	Application* Application::instance = nullptr;

	Application::Application(const WindowProps& windowProps)
	{
		// TODO: this is the best place for this I can think of as of right now
		// but it is not set in stone.
		Log::init();

		GBC_CORE_ASSERT(instance == nullptr, "Attempted to recreate Application!");
		instance = this;

		window = Window::create(windowProps);
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

	void Application::onEvent(Event& e)
	{
		GBC_CORE_TRACE(e);

		if (!layerStack.onEvent(e))
		{
			EventDispatcher dispatcher(e);
			dispatcher.dispatch<WindowCloseEvent>(GBC_BIND_FUNC(Application::onWindowClose));
			dispatcher.dispatch<WindowResizeEvent>(GBC_BIND_FUNC(Application::onWindowResize));
		}
	}

	void Application::run()
	{
		while (running)
		{
			TimeStep ts = window->getElapsedTime();

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

	void Application::terminate()
	{
		running = false;
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		terminate();
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& e)
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

	void Application::pushLayer(Layer* layer)
	{
		layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		layerStack.pushOverlay(overlay);
	}
}
