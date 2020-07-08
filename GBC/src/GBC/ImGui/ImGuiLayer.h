#pragma once

#ifdef GBC_ENABLE_IMGUI
#include "GBC/Layers/Layer.h"

namespace gbc
{
	class ImGuiLayer : public Layer
	{
	public:
		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;
		virtual void onEvent(Event& e) override;

		void begin();
		void end();

		inline void setBlockEvents(bool blockEvents) { this->blockEvents = blockEvents; }
	private:
		bool blockEvents = true;
	};
}
#endif
