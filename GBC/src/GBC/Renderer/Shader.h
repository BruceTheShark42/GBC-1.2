#pragma once

#include <string>

namespace gbc
{
	class Shader
	{
	public:
		Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
		~Shader();

		void bind() const;
		void unbind() const;
	protected:
		unsigned int rendererID;
	};
}
