#include <gbc.h>

class Sandbox : public gbc::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

gbc::Application* gbc::createApplication()
{
	return new Sandbox();
}
