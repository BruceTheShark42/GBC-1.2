#pragma once

#include <gbc.h>
#ifdef GBC_ENABLE_IMGUI

#include "SceneContextPanel.h"

namespace gbc
{
	class SceneHierarchyPanel : public SceneContextPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene) : SceneContextPanel(scene) {}

		virtual void onImGuiRender(TimeStep ts) override;
	private:
		void drawEntityNode(Entity entity);
	private:
		Entity selectionContext;

		friend class PropertiesPanel;
	};
}

#endif
