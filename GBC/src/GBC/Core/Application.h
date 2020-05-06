#pragma once

#include "core.h"
#include "Window.h"
#include "TimeStep.h"
#include "GBC/Events/WindowEvent.h"
#include "GBC/Layers/LayerStack.h"
#include "GBC/ImGui/ImGuiLayer.h"

namespace gbc
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void terminate();

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
