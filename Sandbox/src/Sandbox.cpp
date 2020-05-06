#include <gbc.h>
#include <GBC/Core/entryPoint.h>

// Sandbox2D
#include "Sandbox2D.h"

class Sandbox : public gbc::Application
{
public:
	Sandbox()
	{
		pushLayer(new Sandbox2DLayer());
	}

	~Sandbox()
	{

	}
};

/*
 * Trello: https://trello.com/b/DaO3KVu2/gbc-12
 * GitHub: https://github.com/BruceTheShark42/GBC-1.2
 * Cherno: (DONE WITH) https://www.youtube.com/watch?v=FATUxECqhbg&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=67
 */

gbc::Application* gbc::createApplication()
{
	return new Sandbox();
}
