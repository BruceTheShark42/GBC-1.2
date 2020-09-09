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
		Application(const WindowProps& windowProps = WindowProps());
		virtual ~Application();

		void run();
		void terminate();

		void onEvent(Event& e);
		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);
		
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

#ifdef GBC_ENABLE_IMGUI
		ImGuiLayer* getImGuiLayer() const { return imguiLayer; }
#endif // GBC_IMGUI_ENABLE
		inline static Application& get() { return *instance; }
		inline Window& getWindow() const { return *window; }
	private:
		Scope<Window> window;
		LayerStack layerStack;
#ifdef GBC_ENABLE_IMGUI
		ImGuiLayer* imguiLayer = nullptr;
#endif

		bool running = true, minimized = false;
		static Application* instance;
	};

	Application* createApplication();
}
