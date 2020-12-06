#pragma once

#include <gbc.h>
#ifdef GBC_ENABLE_IMGUI

#include "SceneContextPanel.h"
#include "SceneHierarchyPanel.h"

namespace gbc
{
	class ScenePanel : public SceneContextPanel
	{
	public:
		ScenePanel() = default;
		ScenePanel(SceneHierarchyPanel* sceneHierarchyPanel) : SceneContextPanel(sceneHierarchyPanel->getContext()), sceneHierarchyPanel(sceneHierarchyPanel) {}
		virtual ~ScenePanel() = default;

		virtual void onImGuiRender(TimeStep ts) override;

		inline void setSceneFocused(bool* sceneFocused) { this->sceneFocused = sceneFocused; }
		inline void setSceneHovered(bool* sceneHovered) { this->sceneHovered = sceneHovered; }
		inline void setViewportSize(glm::vec2* viewportSize) { this->viewportSize = viewportSize; }
		inline void setGizmoType(int* gizmoType) { this->gizmoType = gizmoType; }
		inline void setFramebuffer(const Ref<Framebuffer>& fbo) { this->fbo = fbo; }
		inline void setSceneHierarchyPanel(SceneHierarchyPanel* sceneHierarchyPanel) { this->sceneHierarchyPanel = sceneHierarchyPanel; context = sceneHierarchyPanel->getContext(); }
	private:
		bool* sceneFocused = nullptr;
		bool* sceneHovered = nullptr;
		glm::vec2* viewportSize = nullptr;
		int* gizmoType = nullptr;
		Ref<Framebuffer> fbo;

		SceneHierarchyPanel* sceneHierarchyPanel = nullptr;
	};
}

#endif
