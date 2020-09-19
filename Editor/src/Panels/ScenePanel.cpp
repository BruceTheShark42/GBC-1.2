#include "ScenePanel.h"
#ifdef GBC_ENABLE_IMGUI

#include <ImGui/imgui.h>

namespace gbc
{
	void ScenePanel::onImGuiRender(TimeStep ts)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::Begin("Scene");

		*sceneFocused = ImGui::IsWindowFocused();
		*sceneHovered = ImGui::IsWindowHovered();
		Application::get().getImGuiLayer()->setBlockEvents(/*!(*sceneFocused) || */!(*sceneHovered));

		ImVec2 size = ImGui::GetContentRegionAvail();
		*viewportSize = { size.x, size.y };

		ImGui::Image((void*)fbo->getColorAttachment(), size, { 0.0f, 1.0f }, { 1.0f, 0.0f });
		ImGui::End();
		ImGui::PopStyleVar();
	}
}

#endif
