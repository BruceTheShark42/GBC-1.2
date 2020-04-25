#include <gbc.h>
#include <GBC/Core/entryPoint.h>

// Includes for TestLayer
//#ifdef GBC_ENABLE_IMGUI
//	#include <ImGui/imgui.h>
//#endif
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

// Sandbox2D
#include "Sandbox2D.h"

//class TestLayer : public gbc::Layer
//{
//public:
//	TestLayer()
//		: cameraController(1280.0f / 720.0f), color(0.870588f, 0.270588f, 0.270588f)
//	{
//		vao = gbc::VertexArray::create();
//
//		float vertices[4 * 5] = {
//			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 
//			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
//			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
//			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f
//		};
//
//		gbc::Ref<gbc::VertexBuffer> vbo = gbc::VertexBuffer::create(vertices, sizeof(vertices) / sizeof(float));
//		vbo->setLayout({
//			{ gbc::ShaderDataType::Float3, "position" },
//			{ gbc::ShaderDataType::Float2, "texCoord" }
//		});
//		vao->addVertexBuffer(vbo);
//
//		unsigned int indices[6] = {
//			0, 1, 2,
//			2, 3, 0
//		};
//
//		gbc::Ref<gbc::IndexBuffer> ibo = gbc::IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int));
//		vao->setIndexBuffer(ibo);
//
//		shader = gbc::Shader::create("assets/shaders/Plain.glsl");
//		textureShader = gbc::Shader::create("assets/shaders/Texture.glsl");
//
//		texture = gbc::Texture2D::create("assets/textures/ChernoLogo.png");
//		textureShader->bind();
//		textureShader->setInt("tex", 0);
//	}
//
//	void onUpdate(gbc::TimeStep ts) override
//	{
//		cameraController.onUpdate(ts);
//
//		gbc::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
//		gbc::RenderCommand::clear();
//
//		gbc::Renderer::beginScene(cameraController.getCamera());
//
//		shader->bind();
//		shader->setFloat3("color", color);
//
//		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
//		for (int y = 0; y < 20; ++y)
//		{
//			for (int x = 0; x < 20; ++x)
//			{
//				glm::vec3 pos = { x * 0.11f, y * 0.11f, 0.0f };
//				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
//				gbc::Renderer::submit(vao, shader, transform);
//			}
//		}
//
//		texture->bind();
//		gbc::Renderer::submit(vao, textureShader);
//
//		gbc::Renderer::endScene();
//	}
//	
//	void onEvent(gbc::Event &e) override
//	{
//		cameraController.onEvent(e);
//	}
//
//#ifdef GBC_ENABLE_IMGUI
//	void onImGuiRender() override
//	{
//		ImGui::Begin("Settings");
//		ImGui::ColorEdit3("Color", glm::value_ptr(color));
//		ImGui::End();
//	}
//#endif
//private:
//	gbc::Ref<gbc::VertexArray> vao;
//	gbc::Ref<gbc::Shader> shader, textureShader;
//	gbc::Ref<gbc::Texture2D> texture;
//
//	gbc::OrthographicCameraController cameraController;
//
//	glm::vec3 color;
//};

class Sandbox : public gbc::Application
{
public:
	Sandbox()
	{
		//pushLayer(new TestLayer());
		pushLayer(new Sandbox2DLayer());
	}

	~Sandbox()
	{

	}
};

/*
 * Trello: https://trello.com/b/DaO3KVu2/gbc-12
 * GitHub: https://github.com/BruceTheShark42/GBC-1.2
 * Cherno: https://www.youtube.com/watch?v=biGF6oLxgtQ&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=61
 * JSABMS: https://www.youtube.com/watch?v=EzMyMbtLfbQ&list=PLydwAuTBfPJX0dn9OrrHpH0F3hjmPRuXe&index=69
 */

gbc::Application* gbc::createApplication()
{
	return new Sandbox();
}
