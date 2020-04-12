#pragma once

#include "Application.h"

#ifdef GBC_PLATFORM_WINDOWS
extern gbc::Application* gbc::createApplication();

int main()
{
	auto app = gbc::createApplication();
	app->run();
	delete app;
}
#endif
