#pragma once

namespace gbc
{
	enum class RendererAPI
	{
		None, OpenGL
	};

	class Renderer
	{
	public:
		inline static RendererAPI getAPI() { return api; }
	private:
		static RendererAPI api;
	};
}
