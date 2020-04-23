#include "gbcpch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace gbc
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> quadShader, quadTextureShader;
	};

	static Renderer2DStorage *data;

	void Renderer2D::init()
	{
		data = new Renderer2DStorage();
		data->quadVertexArray = VertexArray::create();

		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f
		};

		Ref<VertexBuffer> vbo = VertexBuffer::create(vertices, sizeof(vertices) / sizeof(float));
		vbo->setLayout({
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float2, "texCoord" }
		});
		data->quadVertexArray->addVertexBuffer(vbo);

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		Ref<IndexBuffer> ibo = IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int));
		data->quadVertexArray->setIndexBuffer(ibo);

		data->quadShader = Shader::create("assets/shaders/Shader2D.glsl");
		data->quadTextureShader = Shader::create("assets/shaders/Texture2D.glsl");
		data->quadTextureShader->bind();
		data->quadTextureShader->setInt("tex", 0);
	}

	void Renderer2D::shutdown()
	{
		delete data;
	}

	void Renderer2D::beginScene(const OrthographicCamera &camera)
	{
		data->quadShader->bind();
		data->quadShader->setMat4("projectionView", camera.getProjectionView());
		data->quadTextureShader->bind();
		data->quadTextureShader->setMat4("projectionView", camera.getProjectionView());
	}

	void Renderer2D::endScene()
	{

	}

	void Renderer2D::drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color)
	{
		drawQuad(glm::vec3(position, 0.0f), rotation, scale, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color)
	{
		data->quadShader->bind();
		data->quadShader->setFloat4("color", color);
		
		glm::mat4 transform = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), position), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }), glm::vec3(scale, 0.0f));
		data->quadShader->setMat4("transform", transform);

		data->quadVertexArray->bind();
		RenderCommand::drawIndexed(data->quadVertexArray);
	}

	void Renderer2D::drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec4 &tint)
	{
		drawQuad(glm::vec3(position, 0.0f), rotation, scale, texture, tint);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec4 &tint)
	{
		data->quadTextureShader->bind();
		
		glm::mat4 transform = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), position), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }), glm::vec3(scale, 0.0f));
		data->quadTextureShader->setMat4("transform", transform);
		data->quadTextureShader->setFloat4("tint", tint);

		texture->bind();

		data->quadVertexArray->bind();
		RenderCommand::drawIndexed(data->quadVertexArray);
	}
}
