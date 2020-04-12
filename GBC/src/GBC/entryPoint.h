#pragma once

#ifdef GBC_PLATFORM_WINDOWS
extern gbc::Application* gbc::createApplication();

int main()
{
	gbc::Log::init();
	GBC_CORE_INFO("Log initialized!");
	auto app = gbc::createApplication();
	app->run();
	delete app;
}
#endif
