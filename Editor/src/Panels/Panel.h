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

		inline bool isEnabled() const { return enabled; }
		inline void setEnabled(bool enabled) { this->enabled = enabled; }
		inline void toggleEnabled() { setEnabled(!isEnabled()); }
	protected:
		bool enabled = true;
	};
}

#endif
