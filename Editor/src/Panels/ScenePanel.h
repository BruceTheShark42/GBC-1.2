#pragma once

#include <gbc.h>
#ifdef GBC_ENABLE_IMGUI

#include "SceneContextPanel.h"

namespace gbc
{
	class ScenePanel : public SceneContextPanel
	{
	public:
		ScenePanel() = default;
		ScenePanel(const Ref<Scene>& scene) : SceneContextPanel(scene) {}
		virtual ~ScenePanel() = default;

		virtual void onImGuiRender(TimeStep ts) override;

		inline void setSceneFocused(bool* sceneFocused) { this->sceneFocused = sceneFocused; }
		inline void setSceneHovered(bool* sceneHovered) { this->sceneHovered = sceneHovered; }
		inline void setViewportSize(glm::vec2* viewportSize) { this->viewportSize = viewportSize; }
		inline void setFBO(const Ref<FrameBuffer>& fbo) { this->fbo = fbo; }
	private:
		bool* sceneFocused = nullptr;
		bool* sceneHovered = nullptr;
		glm::vec2* viewportSize = nullptr;
		Ref<FrameBuffer> fbo;
	};
}

#endif
