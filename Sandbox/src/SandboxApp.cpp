#include <gbc.h>
#include <GBC/Core/entryPoint.h>

// Sandbox2D
#include "SandboxLayer.h"

class Sandbox : public gbc::Application
{
public:
	Sandbox()
	{
		pushLayer(new SandboxLayer());
	}

	~Sandbox()
	{

	}
};

/*
 * Trello: https://trello.com/b/DaO3KVu2/gbc-12
 * GitHub: https://github.com/BruceTheShark42/GBC-1.2
 * Cherno: https://www.youtube.com/watch?v=ZVy81M-IST0&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=75
 */

gbc::Application* gbc::createApplication()
{
	return new Sandbox();
}
