#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace gbc
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None, OpenGL
		};

		virtual void clear() = 0;
		virtual void setClearColor(const glm::vec4 &color) = 0;

		virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) = 0;

		inline static API getAPI() { return api; }
	private:
		static API api;
	};


}