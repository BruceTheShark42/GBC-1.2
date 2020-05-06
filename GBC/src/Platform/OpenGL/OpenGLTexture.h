#pragma once

#include "GBC/Renderer/Texture.h"
#include <glad/glad.h>

namespace gbc
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string &path);
		OpenGLTexture2D(unsigned int width, unsigned int height);
		virtual ~OpenGLTexture2D();

		inline virtual unsigned int getWidth() const override { return width; }
		inline virtual unsigned int getHeight() const override { return height; }

		virtual void setData(void *data, unsigned int size) override;

		virtual void bind(unsigned int slot = 0) const override;

		virtual bool operator==(const Texture &texture) override { return rendererID == ((OpenGLTexture2D&)texture).rendererID; }
	private:
#ifdef GBC_DEBUG
		std::string path;
#endif
		unsigned int width, height;
		unsigned int rendererID;
		GLenum internalFormat, dataFormat;
	};
}
