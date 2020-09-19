#pragma once

#include <gbc.h>
#ifdef GBC_ENABLE_IMGUI

#include "SceneContextPanel.h"
#include "SceneHierarchyPanel.h"

namespace gbc
{
	class PropertiesPanel : public SceneContextPanel
	{
	public:
		PropertiesPanel() = default;
		PropertiesPanel(const Ref<Scene>& scene, const SceneHierarchyPanel* sceneHierarchyPanel) : SceneContextPanel(scene), sceneHierarchyPanel(sceneHierarchyPanel) {}
		virtual ~PropertiesPanel() = default;

		inline void setSceneHierarchyPanel(const SceneHierarchyPanel* sceneHierarchyPanel) { this->sceneHierarchyPanel = sceneHierarchyPanel; }

		virtual void onImGuiRender(TimeStep ts) override;
	private:
		void drawComponents(Entity entity);

		const SceneHierarchyPanel* sceneHierarchyPanel = nullptr;
	};
}

#endif
