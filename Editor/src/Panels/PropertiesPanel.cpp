#include "PropertiesPanel.h"
#ifdef GBC_ENABLE_IMGUI

#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace gbc
{
	void PropertiesPanel::onImGuiRender(TimeStep ts)
	{
		if (enabled)
		{
			ImGui::Begin("Properties", &enabled);
			if (sceneHierarchyPanel->selectionContext)
				drawComponents(sceneHierarchyPanel->selectionContext);
			ImGui::End();
		}
	}

	void PropertiesPanel::drawComponents(Entity entity)
	{
		if (entity.has<TagComponent>())
		{
			auto& tag = entity.get<TagComponent>().tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());

			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
				tag = buffer;
		}

		if (entity.has<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.get<TransformComponent>().transform;

				glm::vec3 position(transform[3]);
				float rotation = 0.0f;
				glm::vec3 scale(transform[0][0], transform[1][1], transform[2][2]);

				bool changed = false;
				changed |= ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f);
				changed |= ImGui::DragFloat("Rotation", &rotation);
				changed |= ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f);

				if (changed)
					transform = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), position), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)), scale);

				ImGui::TreePop();
			}
		}

		if (entity.has<SpriteRendererComponent>())
		{
			auto& color = entity.get<SpriteRendererComponent>().color;
			ImGui::ColorEdit4("Color", glm::value_ptr(color));
		}
	}
}

#endif
