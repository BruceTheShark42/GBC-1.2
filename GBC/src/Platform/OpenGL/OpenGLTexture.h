#pragma once

#include "GBC/Renderer/Texture.h"

namespace gbc
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string &path);
		virtual ~OpenGLTexture2D();

		inline virtual unsigned int getWidth() const override { return width; }
		inline virtual unsigned int getHeight() const override { return height; }

		virtual void bind(unsigned int slot = 0) const override;
	private:
#ifdef GBC_DEBUG
		std::string path;
#endif
		unsigned int width, height, channels;
		unsigned int rendererID;
	};
}
