#include "ScenePanel.h"
#ifdef GBC_ENABLE_IMGUI

#include <ImGui/imgui.h>
#include <ImGuizmo.h>

#include <glm/gtc/type_ptr.hpp>

#include "GBC/Math/Math.h"

namespace gbc
{
	void ScenePanel::onImGuiRender(TimeStep ts)
	{
		if (enabled)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
			ImGui::Begin("Scene", &enabled);

			*sceneFocused = ImGui::IsWindowFocused();
			*sceneHovered = ImGui::IsWindowHovered();
			Application::get().getImGuiLayer()->setBlockEvents(/*!(*sceneFocused) || */!(*sceneHovered));

			ImVec2 size = ImGui::GetContentRegionAvail();
			*viewportSize = { size.x, size.y };

			ImGui::Image((void*)(uint64_t)fbo->getColorAttachment(), size, { 0.0f, 1.0f }, { 1.0f, 0.0f });

			// Gizmos
			Entity selectedEntity = sceneHierarchyPanel->getSelectedEntity();
			if (selectedEntity && *gizmoType != -1)
			{
				ImGuizmo::SetOrthographic(false);
				ImGuizmo::SetDrawlist();

				float windowWidth = ImGui::GetWindowWidth();
				float windowHeight = ImGui::GetWindowHeight();
				ImVec2 windowPos = ImGui::GetWindowPos();
				ImGuizmo::SetRect(windowPos.x, windowPos.y, windowWidth, windowHeight);

				auto cameraEntity = context->getPrimaryCameraEntity();
				if (cameraEntity)
				{
					// Camera
					const glm::mat4& cameraProjection = cameraEntity.get<CameraComponent>().camera.getProjection();
					glm::mat4 cameraView = glm::inverse((glm::mat4)cameraEntity.get<TransformComponent>());

					// Entity Transform
					auto& transformComponent = selectedEntity.get<TransformComponent>();
					glm::mat4 transform = transformComponent;

					// Snapping
					bool snap = Input::isKeyPressed(KeyCode::LeftControl);
					float snapValue = 0.5f;
					if (*gizmoType == ImGuizmo::OPERATION::ROTATE)
						snapValue = 45.0f;

					float snapValues[] = { snapValue, snapValue, snapValue };

					ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
						(ImGuizmo::OPERATION)(*gizmoType), ImGuizmo::LOCAL, glm::value_ptr(transform),
						nullptr, snap ? snapValues : nullptr);

					if (ImGuizmo::IsUsing())
					{
						glm::vec3 translation, rotation, scale;
						math::decomposeTransform(transform, translation, rotation, scale);

						transformComponent.translation = translation;
						transformComponent.rotation += rotation - transformComponent.rotation;
						transformComponent.scale = scale;
					}
				}
			}

			ImGui::End();
			ImGui::PopStyleVar();
		}
	}
}

#endif
