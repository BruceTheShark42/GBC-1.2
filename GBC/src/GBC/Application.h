#pragma once

#include "core.h"
#include "Window.h"
#include "Events/WindowEvent.h"

namespace gbc
{
	class GBC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event &e);
		bool onWindowClosedEvent(WindowClosedEvent &e);
	private:
		std::unique_ptr<Window> window;

		bool running;
	};

	Application* createApplication();
}
