#pragma once

#include <gbc.h>

class Sandbox2DLayer : public gbc::Layer
{
public:
	Sandbox2DLayer();
	virtual ~Sandbox2DLayer() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(gbc::TimeStep ts) override;
	virtual void onEvent(gbc::Event &e) override;
#ifdef GBC_ENABLE_IMGUI
	virtual void onImGuiRender();
#endif
private:
	gbc::OrthographicCameraController cameraController;
	glm::vec3 position = { 0.0f, 0.0f, 0.2f };
	float rotation = 0.0f;
	glm::vec2 scale = { 1.0f, 1.0f };
	glm::vec4 color = { 0.870588f, 0.270588f, 0.270588f, 1.0f };
	gbc::Ref<gbc::Texture2D> texture;

	float millis = 0.0f;
};
