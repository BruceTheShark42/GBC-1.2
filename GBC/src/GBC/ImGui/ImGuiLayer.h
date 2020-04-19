#pragma once

#include "GBC/Layers/Layer.h"

namespace gbc
{
	class GBC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate() override;
		virtual void onEvent(Event &e) override;
	private:
		float time;
	};
}
