#include "gbcpch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace gbc
{
	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
		float texIndex;
	};

	struct Renderer2DData
	{
		const unsigned int MAX_QUADS = 10000;
		const unsigned int MAX_VERTICES = MAX_QUADS * 4;
		const unsigned int MAX_INDICES = MAX_QUADS * 6;
		// TODO: query driver (currently in OpenGLContext.cpp)
		static const unsigned int MAX_TEXTURES = 32;

		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> quadShader;
		Ref<Texture2D> whiteTexture;

		unsigned int quadIndexCount = 0;
		QuadVertex *quadBufferBase = nullptr;
		QuadVertex *quadBufferPtr = nullptr;
		
		std::array<Ref<Texture>, MAX_TEXTURES> textureSlots;
		unsigned int textureSlotIndex = 1;

		glm::vec4 quadVertexPositions[4];
	};

	static Renderer2DData data;

	void Renderer2D::init()
	{
		data.quadVertexArray = VertexArray::create();

		data.quadVertexBuffer = VertexBuffer::create(data.MAX_VERTICES * sizeof(QuadVertex));
		data.quadVertexBuffer->setLayout({
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "color" },
			{ ShaderDataType::Float2, "texCoord" },
			{ ShaderDataType::Float, "texIndex" }
		});
		data.quadVertexArray->addVertexBuffer(data.quadVertexBuffer);

		data.quadBufferBase = new QuadVertex[data.MAX_VERTICES];

		unsigned int *quadIndices = new unsigned int[data.MAX_INDICES];
		for (unsigned int i = 0, offset = 0; i < data.MAX_INDICES; i += 6, offset += 4)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
		}

		Ref<IndexBuffer> ibo = IndexBuffer::create(quadIndices, data.MAX_INDICES);
		data.quadVertexArray->setIndexBuffer(ibo);
		delete[] quadIndices;

		data.whiteTexture = Texture2D::create(1, 1);
		unsigned int whiteTextureData = 0xffffffff;
		data.whiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

		int *samplers = new int[data.MAX_TEXTURES];
		for (int i = 0; i < data.MAX_TEXTURES; ++i)
			samplers[i] = i;

		data.quadShader = Shader::create("assets/shaders/Renderer2D.glsl");
		data.quadShader->bind();
		data.quadShader->setIntArray("textures", samplers, data.MAX_TEXTURES);

		data.textureSlots[0] = data.whiteTexture;

		data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		data.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		data.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::shutdown()
	{
		
	}

	void Renderer2D::beginScene(const OrthographicCamera &camera)
	{
		data.quadShader->bind();
		data.quadShader->setMat4("projectionView", camera.getProjectionView());

		data.quadIndexCount = 0;
		data.quadBufferPtr = data.quadBufferBase;

		data.textureSlotIndex = 1;
	}

	void Renderer2D::endScene()
	{
		unsigned int dataSize = (unsigned int)((unsigned char*)data.quadBufferPtr - (unsigned char*)data.quadBufferBase);
		data.quadVertexBuffer->setData(data.quadBufferBase, dataSize);

		flush();
	}

	void Renderer2D::flush()
	{
		for (unsigned int i = 0; i < data.textureSlotIndex; ++i)
			data.textureSlots[i]->bind(i);

		RenderCommand::drawIndexed(data.quadVertexArray, data.quadIndexCount);
	}

	// drawQuad stuff

	// Non-rotated non-scaled quad

	void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec4 &color)
	{
		createQuad(position, 0.0f, { 0.0f, 0.0f }, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor, const glm::vec4 &color)
	{
		float textureIndex = 0.0f;

		for (unsigned int i = 1; i < data.textureSlotIndex; ++i)
		{
			if (*data.textureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)data.textureSlotIndex;
			data.textureSlots[data.textureSlotIndex++] = texture;
		}

		createQuad(position, textureIndex, tilingFactor, color);
	}

	void Renderer2D::createQuad(const glm::vec3 &position, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color)
	{
		const glm::vec2 texCoords[4] = { { 0.0f, 0.0f }, { tilingFactor.x, 0.0f }, { tilingFactor.x, tilingFactor.y }, { 0.0f, tilingFactor.y } };
		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

		for (unsigned char i = 0; i < 4; ++i)
		{
			data.quadBufferPtr->position = transform * data.quadVertexPositions[i];
			data.quadBufferPtr->color = color;
			data.quadBufferPtr->texCoord = texCoords[i];
			data.quadBufferPtr->texIndex = textureIndex;
			++data.quadBufferPtr;
		}

		data.quadIndexCount += 6;
	}

	// Rotated non-scaled quad

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const glm::vec4 &color)
	{
		createQuad(position, rotation, 0.0f, { 0.0f, 0.0f }, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor, const glm::vec4 &color)
	{
		float textureIndex = 0.0f;

		for (unsigned int i = 1; i < data.textureSlotIndex; ++i)
		{
			if (*data.textureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)data.textureSlotIndex;
			data.textureSlots[data.textureSlotIndex++] = texture;
		}

		createQuad(position, rotation, textureIndex, tilingFactor, color);
	}

	void Renderer2D::createQuad(const glm::vec3 &position, float rotation, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color)
	{
		const glm::vec2 texCoords[4] = { { 0.0f, 0.0f }, { tilingFactor.x, 0.0f }, { tilingFactor.x, tilingFactor.y }, { 0.0f, tilingFactor.y } };
		const glm::mat4 transform = glm::rotate(glm::translate(glm::mat4(1.0f), position), rotation, { 0.0f, 0.0f, 1.0f });

		for (unsigned char i = 0; i < 4; ++i)
		{
			data.quadBufferPtr->position = transform * data.quadVertexPositions[i];
			data.quadBufferPtr->color = color;
			data.quadBufferPtr->texCoord = texCoords[i];
			data.quadBufferPtr->texIndex = textureIndex;
			++data.quadBufferPtr;
		}

		data.quadIndexCount += 6;
	}

	// Non-rotated scaled quad

	void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const glm::vec4 &color)
	{
		createQuad(position, scale, 0.0f, { 0.0f, 0.0f }, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor, const glm::vec4 &color)
	{
		float textureIndex = 0.0f;

		for (unsigned int i = 1; i < data.textureSlotIndex; ++i)
		{
			if (*data.textureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)data.textureSlotIndex;
			data.textureSlots[data.textureSlotIndex++] = texture;
		}

		createQuad(position, scale, textureIndex, tilingFactor, color);
	}

	void Renderer2D::createQuad(const glm::vec3 &position, const glm::vec2 &scale, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color)
	{
		const glm::vec2 texCoords[4] = { { 0.0f, 0.0f }, { tilingFactor.x, 0.0f }, { tilingFactor.x, tilingFactor.y }, { 0.0f, tilingFactor.y } };
		const glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), position), { scale, 1.0f });

		for (unsigned char i = 0; i < 4; ++i)
		{
			data.quadBufferPtr->position = transform * data.quadVertexPositions[i];
			data.quadBufferPtr->color = color;
			data.quadBufferPtr->texCoord = texCoords[i];
			data.quadBufferPtr->texIndex = textureIndex;
			++data.quadBufferPtr;
		}

		data.quadIndexCount += 6;
	}

	// Rotated scaled quad

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const glm::vec4 &color)
	{
		createQuad(position, rotation, scale, 0.0f, { 0.0f, 0.0f }, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, const Ref<Texture2D> &texture, const glm::vec2 &tilingFactor, const glm::vec4 &color)
	{
		float textureIndex = 0.0f;

		for (unsigned int i = 1; i < data.textureSlotIndex; ++i)
		{
			if (*data.textureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)data.textureSlotIndex;
			data.textureSlots[data.textureSlotIndex++] = texture;
		}

		createQuad(position, rotation, scale, textureIndex, tilingFactor, color);
	}

	void Renderer2D::createQuad(const glm::vec3 &position, float rotation, const glm::vec2 &scale, float textureIndex, const glm::vec2 &tilingFactor, const glm::vec4 &color)
	{
		const glm::vec2 texCoords[4] = { { 0.0f, 0.0f }, { tilingFactor.x, 0.0f }, { tilingFactor.x, tilingFactor.y }, { 0.0f, tilingFactor.y } };
		const glm::mat4 transform = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), position), rotation, { 0.0f, 0.0f, 1.0f }), { scale, 1.0f });

		for (unsigned char i = 0; i < 4; ++i)
		{
			data.quadBufferPtr->position = transform * data.quadVertexPositions[i];
			data.quadBufferPtr->color = color;
			data.quadBufferPtr->texCoord = texCoords[i];
			data.quadBufferPtr->texIndex = textureIndex;
			++data.quadBufferPtr;
		}

		data.quadIndexCount += 6;
	}
}
