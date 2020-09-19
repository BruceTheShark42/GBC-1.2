#pragma once

#include <gbc.h>
#ifdef GBC_ENABLE_IMGUI

#include "Panel.h"

namespace gbc
{
	class SceneContextPanel : public Panel
	{
	public:
		SceneContextPanel() = default;
		SceneContextPanel(const Ref<Scene>& scene) : context(scene) {}
		virtual ~SceneContextPanel() = default;

		inline void setContext(const Ref<Scene>& scene) { context = scene; }

		virtual void onImGuiRender(TimeStep ts) = 0;
	protected:
		Ref<Scene> context;
	};
}

#endif
