#pragma once

#include "GBC/core.h"
#include "Layer.h"

namespace gbc
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		
		void pushLayer(Layer *layer);
		void pushOverlay(Layer *overlay);
		void popLayer(Layer *layer);
		void popOverlay(Layer *overlay);

		void onUpdate();
		bool onEvent(Event &e);
#ifdef GBC_ENABLE_IMGUI
		void onImGuiRender();
#endif

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
		std::vector<Layer*>::const_iterator begin() const { return layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return layers.end(); }
	private:
		std::vector<Layer*> layers;
		unsigned int layerInsertIndex;
	};
}
