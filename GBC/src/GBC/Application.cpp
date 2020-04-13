#include "gbcpch.h"
#include "Application.h"
#include "Events/WindowEvent.h"

namespace gbc
{
	Application::Application()
		: running(true)
	{

	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		WindowResizedEvent e(1280, 720);
		GBC_INFO(e);

		while (running)
		{

		}
	}
}
