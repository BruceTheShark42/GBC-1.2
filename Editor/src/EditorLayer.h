#pragma once

#include <gbc.h>
#include "Panels/Panel.h"

namespace gbc
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(TimeStep ts) override;
		virtual void onEvent(Event& event) override;
#ifdef GBC_ENABLE_IMGUI
		virtual void onImGuiRender(TimeStep ts) override;
#endif
	private:
#ifdef GBC_ENABLE_IMGUI
		Ref<Framebuffer> framebuffer;
#endif

		std::string sceneFilePath;
		Ref<Scene> scene;

		glm::vec2 viewportSize{ 0.0f, 0.0f };
		bool sceneFocused = false;
		bool sceneHovered = false;
		int gizmoType = -1;

		void newScene();
		void openScene();
		void saveSceneAs();
		void saveScene(const std::string& filePath);

#ifdef GBC_ENABLE_IMGUI
		std::map<std::string, Panel*> panels;
		SceneHierarchyPanel* sceneHierarchyPanel;
#endif
	};
}
