#pragma once

#include "core.h"
#include "Window.h"
#include "Events/WindowEvent.h"
#include "Layers/LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "GBC/Core/TimeStep.h"

namespace gbc
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event &e);
		bool onWindowClosed(WindowClosedEvent &e);
		bool onWindowResized(WindowResizedEvent &e);
		
		void pushLayer(Layer *layer);
		void pushOverlay(Layer *overlay);

		inline static Application& getInstance() { return *instance; }
		inline Window& getWindow() const { return *window; }
	private:
		Scope<Window> window;
		LayerStack layerStack;
#ifdef GBC_ENABLE_IMGUI
		ImGuiLayer *imguiLayer;
#endif

		float lastFrameTime;
		bool running, minimized;
		static Application *instance;
	};

	Application* createApplication();
}
