#include "gbcpch.h"
#include "Application.h"
#include <glad/glad.h>

namespace gbc
{
	Application *Application::instance = nullptr;

	Application::Application()
		: running(true)
	{
		GBC_CORE_ASSERT(instance == nullptr, "Attempted to recreate Application!");
		instance = this;

		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(GBC_BIND_FUNC(Application::onEvent));

#ifdef GBC_ENABLE_IMGUI
		imguiLayer = new ImGuiLayer();
		layerStack.pushOverlay(imguiLayer);
#endif

		vao.reset(VertexArray::create());

		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> vbo;
		vbo.reset(VertexBuffer::create(vertices, sizeof(vertices) / sizeof(float)));
		vbo->setLayout({
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "color" }
		});

		vao->addVertexBuffer(vbo);

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<IndexBuffer> ibo;
		ibo.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));
		vao->setIndexBuffer(ibo);

		shader.reset(new Shader(R"(
			#version 460 core
			
			layout (location = 0) in vec3 position;
			layout (location = 1) in vec4 color;
			
			out vec4 _color;
			
			void main()
			{
				gl_Position = vec4(position, 1.0);
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

	Application::~Application()
	{
		
	}

	void Application::onEvent(Event &e)
	{
		GBC_CORE_TRACE(e);

		if (!layerStack.onEvent(e))
		{
			EventDispatcher dispatcher(e);
			dispatcher.dispatch<WindowClosedEvent>(GBC_BIND_FUNC(Application::onWindowClosedEvent));
		}
	}

	bool Application::onWindowClosedEvent(WindowClosedEvent &e)
	{
		running = false;
		return true;
	}

	void Application::run()
	{
		while (running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->bind();
			vao->bind();
			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

			layerStack.onUpdate();

#ifdef GBC_ENABLE_IMGUI
			imguiLayer->begin();
			layerStack.onImGuiRender();
			imguiLayer->end();
#endif

			window->onUpdate();
		}
	}

	void Application::pushLayer(Layer *layer)
	{
		layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer *overlay)
	{
		layerStack.pushOverlay(overlay);
	}
}
