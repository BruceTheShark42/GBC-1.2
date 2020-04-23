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
		Ref<Shader> quadShader;
		Ref<Texture2D> whiteTexture;
	};

	static Renderer2DStorage *data;

	void Renderer2D::init()
	{
		GBC_CORE_ASSERT(data == nullptr, "Renderer2D reinitialized!");

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

		data->whiteTexture = Texture2D::create(1, 1);
		unsigned int whiteTextureData = 0xffffffff;
		data->whiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

		data->quadShader = Shader::create("assets/shaders/Renderer2D.glsl");
		data->quadShader->bind();
		data->quadShader->setInt("tex", 0);
	}

	void Renderer2D::shutdown()
	{
		delete data;
	}

	void Renderer2D::beginScene(const OrthographicCamera &camera)
	{
		data->quadShader->bind();
		data->quadShader->setMat4("projectionView", camera.getProjectionView());
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
		data->quadShader->setFloat4("color", color);
		data->whiteTexture->bind();

		glm::mat4 transform = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), position), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }), glm::vec3(scale, 0.0f));
		data->quadShader->setMat4("transform", transform);

		data->quadVertexArray->bind();
		RenderCommand::drawIndexed(data->quadVertexArray);
	}

	void Renderer2D::drawQuad(const glm::vec2 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec4 &color)
	{
		drawQuad(glm::vec3(position, 0.0f), rotation, scale, texture, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec4 &color)
	{
		data->quadShader->setFloat4("color", color);
		texture->bind();

		glm::mat4 transform = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), position), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }), glm::vec3(scale, 0.0f));
		data->quadShader->setMat4("transform", transform);

		data->quadVertexArray->bind();
		RenderCommand::drawIndexed(data->quadVertexArray);
	}
}
