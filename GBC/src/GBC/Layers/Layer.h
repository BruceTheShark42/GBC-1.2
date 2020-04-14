#pragma once

#include "GBC/core.h"
#include "GBC/Events/Event.h"

namespace gbc
{
	class GBC_API Layer
	{
	public:
		Layer(bool enabled = true)
			: enabled(enabled) {}
		virtual ~Layer() {}

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event &e) {}

		const inline bool isEnabled() const { return enabled; }
		const inline void setEnabled(bool enabled) { this->enabled = enabled; }
	private:
		bool enabled;
	};
}
