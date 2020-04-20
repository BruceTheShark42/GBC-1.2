#include <gbc.h>
#include <ImGui/imgui.h>

class TestLayer : public gbc::Layer
{
	void onImGuiRender() // override // depending on the configuration, this might break
	{
		ImGui::Begin("Test Window");
		ImGui::Text("This is text!");
		ImGui::End();
	}
};

class Sandbox : public gbc::Application
{
public:
	Sandbox()
	{
		pushOverlay(new TestLayer());
	}

	~Sandbox()
	{

	}
};

/*
 * Trello: https://trello.com/b/DaO3KVu2/gbc-12
 * GitHub: https://github.com/BruceTheShark42/GBC-1.2
 * Cherno: https://www.youtube.com/watch?v=akxevYYWd9g&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=33
 * JSABMS: https://www.youtube.com/watch?v=EzMyMbtLfbQ&list=PLydwAuTBfPJX0dn9OrrHpH0F3hjmPRuXe&index=69
 */

gbc::Application* gbc::createApplication()
{
	return new Sandbox();
}
