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

			// Right click on blank space
			if (ImGui::BeginPopupContextWindow(nullptr, 1, false))
			{
				if (ImGui::MenuItem("Create Empty Entity"))
					context->createEntity("Empty Entity");

				ImGui::EndPopup();
			}

			ImGui::End();
		}
	}

	void SceneHierarchyPanel::drawEntityNode(Entity entity)
	{
		auto& tag = entity.get<TagComponent>().tag;

		ImGuiTreeNodeFlags flags = (selectionContext == entity ? ImGuiTreeNodeFlags_Selected : 0)
			| ImGuiTreeNodeFlags_OpenOnArrow/* | ImGuiTreeNodeFlags_SpanAllAvailWidth*/;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)((uint32_t)entity), flags, tag.c_str());

		if (ImGui::IsItemClicked())
			selectionContext = entity;

		// Right click on blank space
		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
			ImGui::TreePop();

		if (entityDeleted)
		{
			context->destroyEntity(entity);
			if (selectionContext == entity)
				selectionContext = {};
		}
	}
}

#endif
