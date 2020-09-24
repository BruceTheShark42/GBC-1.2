#include <gbc.h>
#include <GBC/Core/entryPoint.h>

#include "EditorLayer.h"

namespace gbc
{
	class Editor : public Application
	{
	public:
		Editor()
			: Application(WindowProps(1280, 720, "GBC-1.2 Editor", true, false, true, false, true))
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
	 * Cherno: https://www.youtube.com/watch?v=RIMt_6agUiU&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=86
	 */

	Application* createApplication()
	{
		return new Editor();
	}
}
