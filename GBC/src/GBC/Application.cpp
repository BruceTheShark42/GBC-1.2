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

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		float vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		shader.reset(new Shader(R"(
			#version 460 core
			
			layout (location = 0) in vec3 position;
			
			out vec4 _color;
			
			void main()
			{
				gl_Position = vec4(position, 1.0);
				_color = vec4(position.x + 0.5, position.y + 0.5, 0.0, 1.0);
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
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
