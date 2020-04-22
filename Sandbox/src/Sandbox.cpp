#include <gbc.h>
#include <ImGui/imgui.h>

class TestLayer : public gbc::Layer
{
public:
	TestLayer()
		: cameraPos(0.0f), cameraRotation(0.0f)
	{
		vao.reset(gbc::VertexArray::create());

		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
		};

		std::shared_ptr<gbc::VertexBuffer> vbo;
		vbo.reset(gbc::VertexBuffer::create(vertices, sizeof(vertices) / sizeof(float)));
		vbo->setLayout({
			{ gbc::ShaderDataType::Float3, "position" },
			{ gbc::ShaderDataType::Float4, "color" }
		});

		vao->addVertexBuffer(vbo);

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<gbc::IndexBuffer> ibo;
		ibo.reset(gbc::IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));
		vao->setIndexBuffer(ibo);

		shader.reset(new gbc::Shader(R"(
			#version 460 core
			
			layout (location = 0) in vec3 position;
			layout (location = 1) in vec4 color;
			
			out vec4 _color;
			
			uniform mat4 projectionView;

			void main()
			{
				gl_Position = projectionView * vec4(position, 1.0);
				_color = color;
			}
		)", R"(
			#version 460 core
			
			in vec4 _color;
			
			out vec4 outColor;
			
			void main()
			{
				outColor = _color;
			}
		)"));
	}

	void onUpdate(gbc::TimeStep ts) override
	{
		gbc::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		gbc::RenderCommand::clear();

		if (gbc::Input::isKeyPressed(GBC_KEY_W))
			cameraPos.y += cameraSpeed * ts;
		if (gbc::Input::isKeyPressed(GBC_KEY_S))
			cameraPos.y -= cameraSpeed * ts;
		if (gbc::Input::isKeyPressed(GBC_KEY_A))
			cameraPos.x -= cameraSpeed * ts;
		if (gbc::Input::isKeyPressed(GBC_KEY_D))
			cameraPos.x += cameraSpeed * ts;

		if (gbc::Input::isKeyPressed(GBC_KEY_LEFT))
			cameraRotation += cameraRotSpeed * ts.seconds();
		if (gbc::Input::isKeyPressed(GBC_KEY_RIGHT))
			cameraRotation -= cameraRotSpeed * ts.seconds();

		camera.setPosition(cameraPos);
		camera.setRotation(cameraRotation);

		gbc::Renderer::beginScene(camera);
		shader->bind();
		shader->setUniform("projectionView", camera.getProjectionView());
		gbc::Renderer::submit(vao);
		gbc::Renderer::endScene();

	}
	
	void onEvent(gbc::Event &e) override
	{
		
	}

	void onImGuiRender() // override // this breaks in Dist because ImGui is completely stripped from it
	{
		ImGui::Begin("Test Window");
		ImGui::Text("This is text!");
		ImGui::End();
	}
private:
	std::shared_ptr<gbc::VertexArray> vao;
	std::shared_ptr<gbc::Shader> shader;
	gbc::OrthographicCamera camera;
	glm::vec3 cameraPos;
	float cameraRotation;
	float cameraSpeed = 1.0f, cameraRotSpeed = 180.0f;
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
 * Cherno: https://www.youtube.com/watch?v=cbB2fh0UxZ0&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=38 9:14
 * JSABMS: https://www.youtube.com/watch?v=EzMyMbtLfbQ&list=PLydwAuTBfPJX0dn9OrrHpH0F3hjmPRuXe&index=69
 */

gbc::Application* gbc::createApplication()
{
	return new Sandbox();
}
