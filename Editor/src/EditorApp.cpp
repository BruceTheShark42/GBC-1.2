#include <gbc.h>
#include <GBC/Core/entryPoint.h>

// Sandbox2D
#include "EditorLayer.h"

namespace gbc
{
	class Editor : public Application
	{
	public:
		Editor()
		{
			pushLayer(new EditorLayer());
		}

		~Editor()
		{

		}
	};

	/*
	 * Trello: https://trello.com/b/DaO3KVu2/gbc-12
	 * GitHub: https://github.com/BruceTheShark42/GBC-1.2
	 * Cherno: https://www.youtube.com/watch?v=UljMVrQ_zYY&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=70
	 */

	Application* createApplication()
	{
		return new Editor();
	}
}
