#pragma once

#include <gbc.h>

namespace gbc
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);
	public:
		void setContext(const Ref<Scene>& scene);

		void onImGuiRender();
	private:
		void drawEntityNode(Entity entity);
	private:
		Ref<Scene> context;
		Entity selectionContext;
	};
}
