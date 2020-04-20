#pragma once

#include "GBC/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace gbc
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow *window);

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow *window;
	};
}
