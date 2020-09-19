#include "StatisticsPanel.h"
#ifdef GBC_ENABLE_IMGUI

#include <ImGui/imgui.h>
#include "GBC/Renderer/Renderer2D.h"

namespace gbc
{
	void StatisticsPanel::onImGuiRender(TimeStep ts)
	{
		if (enabled)
		{
			const auto& stats = Renderer2D::getStatistics();
			ImGui::Begin("Statistics", &enabled);
			ImGui::Text("FPS: %.0f", 1.0f / ts);
			ImGui::Text("Draw Calls: %d", stats.drawCalls);
			ImGui::Text("Quads");
			ImGui::Text(" - Count: %d", stats.quadCount);
			ImGui::Text(" - Index Count: %d", stats.getIndexCount());
			ImGui::Text(" - Vertex Count: %d", stats.getVertexCount());
			ImGui::End();
		}
	}
}

#endif
