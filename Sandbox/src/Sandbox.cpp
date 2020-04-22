#include <gbc.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TestLayer : public gbc::Layer
{
public:
	TestLayer()
		: cameraPos(0.0f), cameraRotation(0.0f), camera(-1.6f, 1.6f, -0.9f, 0.9f), color(0.870588f, 0.270588f, 0.270588f)
	{
		vao.reset(gbc::VertexArray::create());

		float vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f, // 0.0f, 0.0f, 0.0f, 1.0f, 
			 0.5f, -0.5f, 0.0f, // 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, // 0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, // 0.0f, 0.0f, 1.0f, 1.0f
		};

		gbc::Ref<gbc::VertexBuffer> vbo;
		vbo.reset(gbc::VertexBuffer::create(vertices, sizeof(vertices) / sizeof(float)));
		vbo->setLayout({
			{ gbc::ShaderDataType::Float3, "position" }/*,
			{ gbc::ShaderDataType::Float4, "color" }*/
		});

		vao->addVertexBuffer(vbo);

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		gbc::Ref<gbc::IndexBuffer> ibo;
		ibo.reset(gbc::IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));
		vao->setIndexBuffer(ibo);

		shader.reset(gbc::Shader::create(R"(
			#version 460 core
			
			layout (location = 0) in vec3 position;
			//layout (location = 1) in vec4 color;
			
			//out vec4 _color;

			uniform mat4 projectionView;
			uniform mat4 transform;

			void main()
			{
				gl_Position = projectionView * transform * vec4(position, 1.0);
				//_color = color;
			}
		)", R"(
			#version 460 core
			
			//in vec4 _color;
			uniform vec3 color;
			
			out vec4 outColor;
			
			void main()
			{
				//outColor = _color;
				outColor = vec4(color, 1.0);
			}
		)"));
	}

	void onUpdate(gbc::TimeStep ts) override
	{
		gbc::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		gbc::RenderCommand::clear();

		if (gbc::Input::isKeyPressed(GBC_KEY_W))
		{
			cameraPos.y += cameraSpeed * cos(glm::radians(cameraRotation)) * ts;
			cameraPos.x -= cameraSpeed * sin(glm::radians(cameraRotation)) * ts;
		}
		if (gbc::Input::isKeyPressed(GBC_KEY_S))
		{
			cameraPos.y -= cameraSpeed * cos(glm::radians(cameraRotation)) * ts;
			cameraPos.x += cameraSpeed * sin(glm::radians(cameraRotation)) * ts;
		}
		if (gbc::Input::isKeyPressed(GBC_KEY_A))
		{
			cameraPos.x -= cameraSpeed * cos(glm::radians(cameraRotation)) * ts;
			cameraPos.y -= cameraSpeed * sin(glm::radians(cameraRotation)) * ts;
		}
		if (gbc::Input::isKeyPressed(GBC_KEY_D))
		{
			cameraPos.x += cameraSpeed * cos(glm::radians(cameraRotation)) * ts;
			cameraPos.y += cameraSpeed * sin(glm::radians(cameraRotation)) * ts;
		}

		if (gbc::Input::isKeyPressed(GBC_KEY_LEFT))
			cameraRotation += cameraRotSpeed * ts;
		if (gbc::Input::isKeyPressed(GBC_KEY_RIGHT))
			cameraRotation -= cameraRotSpeed * ts;

		camera.setPosition(cameraPos);
		camera.setRotation(cameraRotation);

		gbc::Renderer::beginScene(camera);

		std::dynamic_pointer_cast<gbc::OpenGLShader>(shader)->bind();
		std::dynamic_pointer_cast<gbc::OpenGLShader>(shader)->setUniform("color", color);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = -10; y < 11; ++y)
		{
			for (int x = -10; x < 11; ++x)
			{
				glm::vec3 pos = { x * 0.11f, y * 0.11f, 0.0f };
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				gbc::Renderer::submit(vao, shader, transform);
			}
		}
		gbc::Renderer::endScene();
	}
	
	void onEvent(gbc::Event &e) override
	{
		
	}

	void onImGuiRender() // override // this breaks in Dist because ImGui is completely stripped from it
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color", glm::value_ptr(color));
		ImGui::End();
	}
private:
	gbc::Ref<gbc::VertexArray> vao;
	gbc::Ref<gbc::Shader> shader;
	gbc::OrthographicCamera camera;
	glm::vec3 cameraPos;
	float cameraRotation;
	float cameraSpeed = 1.0f, cameraRotSpeed = 180.0f;
	glm::vec3 color;
};

class Sandbox : public gbc::Application
{
public:
	Sandbox()
	{
		pushOverlay(new TestLayer());
	}

	~Sandbox()
	{

	}
};

/*
 * Trello: https://trello.com/b/DaO3KVu2/gbc-12
 * GitHub: https://github.com/BruceTheShark42/GBC-1.2
 * Cherno: https://www.youtube.com/watch?v=qEfohFgQ1-I&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=42
 * JSABMS: https://www.youtube.com/watch?v=EzMyMbtLfbQ&list=PLydwAuTBfPJX0dn9OrrHpH0F3hjmPRuXe&index=69
 */

gbc::Application* gbc::createApplication()
{
	return new Sandbox();
}
