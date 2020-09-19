#pragma once

#include "GBC/Core/core.h"
#ifdef GBC_ENABLE_IMGUI

namespace gbc
{
	class Panel
	{
	public:
		virtual ~Panel() = default;

		virtual void onImGuiRender(TimeStep ts) = 0;
	};
}

#endif
