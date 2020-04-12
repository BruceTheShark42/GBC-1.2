#pragma once

#include "core.h"

namespace gbc
{
	class GBC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	private:
		bool running;
	};

	Application* createApplication();
}
