#include "SceneHierarchyPanel.h"
#include <ImGui/imgui.h>

namespace gbc
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
	{
		setContext(scene);
	}

	void SceneHierarchyPanel::setContext(const Ref<Scene>& scene)
	{
		context = scene;
	}

	void SceneHierarchyPanel::onImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		context->registry.each([&](entt::entity entityID)
		{
			Entity entity{ entityID, context.get() };
			drawEntityNode(entity);
		});

		ImGui::End();
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
