#include "PropertiesPanel.h"
#ifdef GBC_ENABLE_IMGUI

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#include <glm/gtc/type_ptr.hpp>

namespace gbc
{
	static void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float speed = 0.1f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, speed);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.7f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.2f, 0.7f, 0.3f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, speed);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, speed);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
	}

	void PropertiesPanel::onImGuiRender(TimeStep ts)
	{
		Entity& entity = sceneHierarchyPanel->selectionContext;

		if (enabled)
		{
			ImGui::Begin("Properties", &enabled);
			if (entity)
				drawComponents(entity);
			ImGui::End();
		}
	}

	template<typename T, typename UIFunc>
	void drawComponent(const std::string& name, Entity entity, UIFunc uiFunction)
	{
		if (entity.has<T>())
		{
			const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
				ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

			auto& component = entity.get<T>();

			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4.0f, 4.0f });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, name.c_str());
			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", { lineHeight, lineHeight }))
				ImGui::OpenPopup("ComponentSettings");

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.remove<T>();
		}
	}

	template<typename T>
	static void drawRemoveComponent(const std::string& name, Entity entity)
	{
		if (!entity.has<T>() && ImGui::MenuItem(name.c_str()))
		{
			entity.add<T>();
			ImGui::CloseCurrentPopup();
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

			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
				tag = buffer;
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1.0f);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			drawRemoveComponent<TransformComponent>("Transform", entity);
			drawRemoveComponent<CameraComponent>("Camera", entity);
			drawRemoveComponent<SpriteRendererComponent>("Sprite Renderer", entity);
			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		drawComponent<TransformComponent>("Transform", entity, [](TransformComponent& component)
		{
			drawVec3Control("Translation", component.translation);
			glm::vec3 rotation = glm::degrees(component.rotation);
			drawVec3Control("Rotation", rotation, 0.0f, 1.0f);
			component.rotation = glm::radians(rotation);
			drawVec3Control("Scale", component.scale, 1.0f);
		});

		drawComponent<CameraComponent>("Camera", entity, [](CameraComponent& component)
		{
			auto& camera = component.camera;

			ImGui::Checkbox("Primary", &component.primary);

			constexpr const char* projectionTypeNames[] = { "Perspective", "Orthographic" };
			int currentProjectionType = static_cast<int>(camera.getProjectionType());
			const char* currentProjectionTypeName = projectionTypeNames[currentProjectionType];

			if (ImGui::BeginCombo("Projection", currentProjectionTypeName))
			{
				for (int i = 0; i < sizeof(projectionTypeNames) / sizeof(const char*); i++)
				{
					bool selected = i == currentProjectionType;
					if (ImGui::Selectable(projectionTypeNames[i], &selected))
					{
						currentProjectionType = i;
						camera.setProjectionType(static_cast<SceneCamera::ProjectionType>(i));
					}

					if (selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			switch (camera.getProjectionType())
			{
				case SceneCamera::ProjectionType::Perspective:
				{
					float perspectiveFOV = glm::degrees(camera.getPerspectiveFOV());
					if (ImGui::DragFloat("Size", &perspectiveFOV), 0.1f)
						camera.setPerspectiveFOV(glm::radians(perspectiveFOV));

					float perspectiveNearClip = camera.getPerspectiveNearClip();
					if (ImGui::DragFloat("Near Clip", &perspectiveNearClip), 0.1f)
						camera.setPerspectiveNearClip(perspectiveNearClip);

					float perspectiveFarClip = camera.getPerspectiveFarClip();
					if (ImGui::DragFloat("Far Clip", &perspectiveFarClip), 0.1f)
						camera.setPerspectiveFarClip(perspectiveFarClip);

					break;
				}
				case SceneCamera::ProjectionType::Orthographic:
				{
					float orthographicSize = camera.getOrthographicSize();
					if (ImGui::DragFloat("Size", &orthographicSize), 0.1f)
						camera.setOrthographicSize(orthographicSize);

					float orthographicNearClip = camera.getOrthographicNearClip();
					if (ImGui::DragFloat("Near Clip", &orthographicNearClip), 0.1f)
						camera.setOrthographicNearClip(orthographicNearClip);

					float orthographicFarClip = camera.getOrthographicFarClip();
					if (ImGui::DragFloat("Far Clip", &orthographicFarClip), 0.1f)
						camera.setOrthographicFarClip(orthographicFarClip);

					ImGui::Checkbox("Fixed Aspect Ratio", &component.fixedAspectRatio);
					break;
				}
			}
		});

		drawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [](SpriteRendererComponent& component)
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(component.color));
		});
	}
}

#endif
