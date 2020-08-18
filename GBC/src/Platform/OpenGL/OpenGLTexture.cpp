#include "gbcpch.h"
#include "OpenGLTexture.h"
#include <stb_image.h>

namespace gbc
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
#ifdef GBC_DEBUG
		: path(path)
#endif
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		GBC_CORE_ASSERT(data != nullptr, "Failed to load texture!");
		this->width = (unsigned int)width;
		this->height = (unsigned int)height;

		internalFormat = 0;
		dataFormat = 0;
		switch (channels)
		{
			case 3: internalFormat = GL_RGB8; dataFormat = GL_RGB; break;
			case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
		}
		GBC_CORE_ASSERT(internalFormat & dataFormat, "Unknown texture format!");

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, width, height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(unsigned int width, unsigned int height)
		: width(width), height(height)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, width, height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererID);
	}

	void OpenGLTexture2D::setData(void* data, unsigned int size)
	{
		unsigned int bpp = dataFormat == GL_RGBA ? 4 : 3;
		GBC_CORE_ASSERT(size == width * height * bpp, "Data size is too big or too small!");
		glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, rendererID);
	}
}
