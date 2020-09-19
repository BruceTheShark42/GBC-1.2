#include "SceneHierarchyPanel.h"
#ifdef GBC_ENABLE_IMGUI

#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace gbc
{
	void SceneHierarchyPanel::onImGuiRender(TimeStep ts)
	{
		if (enabled)
		{
			ImGui::Begin("Scene Hierarchy", &enabled);
			context->registry.each([&](entt::entity entityID)
			{
				drawEntityNode({ entityID, context.get() });
			});

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				selectionContext = {};
			ImGui::End();
		}
	}

	void SceneHierarchyPanel::drawEntityNode(Entity entity)
	{
		auto& tag = entity.get<TagComponent>().tag;

		ImGuiTreeNodeFlags flags = (selectionContext == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)((uint32_t)entity), flags, tag.c_str());

		if (ImGui::IsItemClicked())
			selectionContext = entity;

		if (opened)
			ImGui::TreePop();
	}
}

#endif
