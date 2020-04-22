#include "gbcpch.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include "stb_image.h"

namespace gbc
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string &path)
#ifdef GBC_DEBUG
		: path(path)
#endif
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		GBC_CORE_ASSERT(data != nullptr, "Failed to load texture!");
		this->width = (unsigned int)width;
		this->height = (unsigned int)height;

		GLenum internalFormat = 0, dataFormat = 0;
		switch (channels)
		{
			case 3: internalFormat = GL_RGB8; dataFormat = GL_RGB; break;
			case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
		}
		GBC_CORE_ASSERT(internalFormat & dataFormat, "Unknown texture format!");

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, width, height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererID);
	}

	void OpenGLTexture2D::bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, rendererID);
	}
}
