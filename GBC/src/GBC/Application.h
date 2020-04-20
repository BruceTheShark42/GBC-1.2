#pragma once

#include "core.h"
#include "Window.h"
#include "Events/WindowEvent.h"
#include "Layers/LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "GBC/Renderer/Shader.h"
#include "GBC/Renderer/Buffer.h"
#include "GBC/Renderer/VertexArray.h"

namespace gbc
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event &e);
		bool onWindowClosedEvent(WindowClosedEvent &e);
		
		void pushLayer(Layer *layer);
		void pushOverlay(Layer *overlay);

		inline static Application& getInstance() { return *instance; }
		inline Window& getWindow() const { return *window; }
	private:
		std::unique_ptr<Window> window;
#ifdef GBC_ENABLE_IMGUI
		ImGuiLayer *imguiLayer;
#endif

		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<Shader> shader;

		LayerStack layerStack;

		bool running;
		static Application *instance;
	};

	Application* createApplication();
}
