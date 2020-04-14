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

/*
 * Trello: https://trello.com/b/DaO3KVu2/gbc-12
 * GitHub: https://github.com/BruceTheShark42/GBC-1.2
 * Cherno: https://www.youtube.com/watch?v=88dmtleVywk&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=11 17:39
 */

gbc::Application* gbc::createApplication()
{
	return new Sandbox();
}
