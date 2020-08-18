#include "gbcpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace gbc
{
	RendererAPI* RenderCommand::api = new OpenGLRendererAPI();
}
