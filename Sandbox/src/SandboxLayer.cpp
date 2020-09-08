#include "SandboxLayer.h"

#ifdef GBC_ENABLE_IMGUI
	#include <ImGui/imgui.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

SandboxLayer::SandboxLayer()
	: cameraController(1280.0f / 720.0f)
{
	cameraController.setZoomLevel(5.0f);
}

void SandboxLayer::onAttach()
{
	texture = gbc::Texture2D::create("assets/textures/checkerBoard.png");
	spriteSheet = gbc::Texture2D::create("assets/textures/RPGpack_sheet_2X.png");
	stairs = gbc::SubTexture2D::createFromCoords(spriteSheet, { 128.0f, 128.0f }, { 2.0f, 1.0f }, { 1.0f, 2.0f });
}

void SandboxLayer::onDetach()
{

}

void SandboxLayer::onUpdate(gbc::TimeStep ts)
{
	// Update
	cameraController.onUpdate(ts);
	millis = ts.millis();
	rotation += 90.0f * ts;

	// Render
	gbc::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	gbc::RenderCommand::clear();
#ifdef GBC_ENABLE_STATS
	gbc::Renderer2D::resetStatistics();
#endif

	gbc::Renderer2D::beginScene(cameraController.getCamera());
	gbc::Renderer2D::drawQuad(position, glm::radians(rotation), scale, texture, { 2.0f, 4.0f }, color);
	gbc::Renderer2D::drawQuad({ -1.0f, 0.5f, 0.2f }, { 1.0f, 1.0f }, { 0.5f, 0.7f, 0.8f, 1.0f });
	gbc::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 16.0f, 16.0f }, texture, { 16.0f, 16.0f });

	for (float y = -5.0f; y <= 5.0f; y += 0.5f)
		for (float x = -5.0f; x <= 5.0f; x += 0.5f)
			gbc::Renderer2D::drawQuad({ x, y, 0.1f }, { 0.45f, 0.45f }, { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f });

	gbc::Renderer2D::drawQuad({ 0.0f, 0.0f, 0.3f }, { 1.0f, 2.0f }, stairs);
	gbc::Renderer2D::endScene();
}

void SandboxLayer::onEvent(gbc::Event& e)
{
	cameraController.onEvent(e);

	if (e.getType() == gbc::EventType::KeyPressed)
	{
		const gbc::KeyPressedEvent& kpe = (gbc::KeyPressedEvent&)e;
		switch (kpe.getKeyCode())
		{
			case gbc::KeyCode::F9:
				if (!kpe.hasRepeated())
					gbc::Application::getInstance().getWindow().toggleVSync();
				break;
			case gbc::KeyCode::F10:
				if (!kpe.hasRepeated())
					gbc::Application::getInstance().getWindow().toggleCursorEnabled();
				break;
			case gbc::KeyCode::F11:
				if (!kpe.hasRepeated())
					gbc::Application::getInstance().getWindow().toggleFullscreen();
				break;
			case gbc::KeyCode::Escape:
				gbc::Application::getInstance().terminate();
				break;
		}
	}
}

#ifdef GBC_ENABLE_IMGUI
void SandboxLayer::onImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::DragFloat2("Position", glm::value_ptr(position));
	ImGui::DragFloat("Rotation", &rotation);
	ImGui::DragFloat2("Scale", glm::value_ptr(scale));
	ImGui::ColorEdit4("Color", glm::value_ptr(color));
	ImGui::End();

	const gbc::Renderer2D::Statistics stats = gbc::Renderer2D::getStatistics();
	ImGui::Begin("Statistics");
	ImGui::Text("Millis Per Frame: %f", millis);
	ImGui::Text("Draw Calls: %d", stats.drawCalls);
	ImGui::Text("Quads");
	ImGui::Text(" - Count: %d", stats.quadCount);
	ImGui::Text(" - Index Count: %d", stats.getIndexCount());
	ImGui::Text(" - Vertex Count: %d", stats.getVertexCount());
	ImGui::End();
}
#endif
