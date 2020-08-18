#pragma once

#include <gbc.h>

namespace gbc
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(TimeStep ts) override;
		virtual void onEvent(Event& e) override;
#ifdef GBC_ENABLE_IMGUI
		virtual void onImGuiRender();
#endif
	private:
		OrthographicCameraController cameraController;
		glm::vec3 position = { 0.0f, 0.0f, 0.2f };
		float rotation = 0.0f;
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> texture;
		Ref<Texture2D> spriteSheet;
		Ref<SubTexture2D> stairs;
		Ref<FrameBuffer> fbo;

		Ref<Scene> scene;
		Entity squareEntity;
		Entity cameraEntity;
		Entity secondCamera;
		bool primaryCamera = true;

		glm::vec2 sceneSize = { 0.0f, 0.0f };
		bool sceneFocused = false, sceneHovered = false;

		// TODO: Should be moved into Renderer2D::Statistics
		float millis = 0.0f;
	};
}
