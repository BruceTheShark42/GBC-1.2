#pragma once

#include <gbc.h>
#ifdef GBC_ENABLE_IMGUI

#include "Panel.h"

namespace gbc
{
	class StatisticsPanel : public Panel
	{
	public:
		virtual void onImGuiRender(TimeStep ts) override;
	};
}

#endif
