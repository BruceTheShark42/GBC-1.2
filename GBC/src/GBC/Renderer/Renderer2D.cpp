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

	// Axis-aligned non-scaled quad

	void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec4 &color)
	{
		data->whiteTexture->bind();
		_drawQuad(position, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &color)
	{
		texture->bind();
		data->quadShader->setFloat("tilingFactor", tilingFactor);
		_drawQuad(position, color);
	}

	void Renderer2D::_drawQuad(const glm::vec3 &position, const glm::vec4 &color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		_drawQuad(transform, color);
	}

	// Axis-aligned scaled quad

	void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const glm::vec4 &color)
	{
		data->whiteTexture->bind();
		_drawQuad(position, scale, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &color)
	{
		texture->bind();
		data->quadShader->setFloat("tilingFactor", tilingFactor);
		_drawQuad(position, scale, color);
	}

	void Renderer2D::_drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const glm::vec4 &color)
	{
		glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), position), glm::vec3(scale, 0.0f));
		_drawQuad(transform, color);
	}

	// Non-axis-aligned scaled quad

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const glm::vec4 &color)
	{
		data->whiteTexture->bind();
		_drawQuad(position, rotation, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &color)
	{
		texture->bind();
		data->quadShader->setFloat("tilingFactor", tilingFactor);
		_drawQuad(position, rotation, color);
	}

	void Renderer2D::_drawQuad(const glm::vec3 &position, float rotation, const glm::vec4 &color)
	{
		glm::mat4 transform = glm::rotate(glm::translate(glm::mat4(1.0f), position), glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
		_drawQuad(transform, color);
	}

	// Non-axis-aligned scaled quad

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color)
	{
		data->whiteTexture->bind();
		_drawQuad(position, rotation, scale, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &color)
	{
		texture->bind();
		data->quadShader->setFloat("tilingFactor", tilingFactor);
		_drawQuad(position, rotation, scale, color);
	}

	void Renderer2D::_drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color)
	{
		glm::mat4 transform = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), position), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }), glm::vec3(scale, 0.0f));
		_drawQuad(transform, color);
	}

	// Generic _drawQuad

	void Renderer2D::_drawQuad(const glm::mat4 &transform, const glm::vec4 &color)
	{
		data->quadShader->setMat4("transform", transform);
		data->quadShader->setFloat4("color", color);

		data->quadVertexArray->bind();
		RenderCommand::drawIndexed(data->quadVertexArray);
	}
}
