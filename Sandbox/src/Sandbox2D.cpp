#include "Sandbox2D.h"

#ifdef GBC_ENABLE_IMGUI
	#include <ImGui/imgui.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2DLayer::Sandbox2DLayer()
	: cameraController(1280.0f / 720.0f)
{

}

void Sandbox2DLayer::onAttach()
{
	texture = gbc::Texture2D::create("assets/textures/checkerBoard.png");
}

void Sandbox2DLayer::onDetach()
{

}

void Sandbox2DLayer::onUpdate(gbc::TimeStep ts)
{
	// Update
	cameraController.onUpdate(ts);

	// Render
	gbc::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	gbc::RenderCommand::clear();

	gbc::Renderer2D::beginScene(cameraController.getCamera());
	gbc::Renderer2D::drawQuad(position, rotation, scale, texture, color);
	gbc::Renderer2D::endScene();
}

void Sandbox2DLayer::onEvent(gbc::Event &e)
{
	cameraController.onEvent(e);
}

#ifdef GBC_ENABLE_IMGUI
void Sandbox2DLayer::onImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::DragFloat2("Position", glm::value_ptr(position));
	ImGui::DragFloat("Rotation", &rotation);
	ImGui::DragFloat2("Scale", glm::value_ptr(scale));
	ImGui::ColorEdit4("Color", glm::value_ptr(color));
	ImGui::End();
}
#endif
