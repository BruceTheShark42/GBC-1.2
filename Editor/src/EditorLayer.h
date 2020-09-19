#pragma once

#include <gbc.h>
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/StatisticsPanel.h"
#include "Panels/PropertiesPanel.h"
#include "Panels/ScenePanel.h"

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
		Ref<FrameBuffer> fbo;
#endif

		Ref<Scene> scene;
		Entity squareEntity;
		Entity primaryCamera;

		glm::vec2 viewportSize = { 0.0f, 0.0f };
		bool sceneFocused = false;
		bool sceneHovered = false;

#ifdef GBC_ENABLE_IMGUI
		// Panels
		SceneHierarchyPanel sceneHierarchyPanel;
		StatisticsPanel statisticsPanel;
		PropertiesPanel propertiesPanel;
		ScenePanel scenePanel;
#endif
	};
}
