#pragma once

#include "GBC/core.h"
#include "GBC/Events/Event.h"

namespace gbc
{
	class Layer
	{
	public:
		Layer(bool enabled = true)
			: enabled(enabled) {}
		virtual ~Layer() {}

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event &e) {}
#ifdef GBC_ENABLE_IMGUI
		virtual void onImGuiRender() {}
#endif

		const inline bool isEnabled() const { return enabled; }
		const inline void setEnabled(bool enabled) { this->enabled = enabled; }
	private:
		bool enabled;
	};
}