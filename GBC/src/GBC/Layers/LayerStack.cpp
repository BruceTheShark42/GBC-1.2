#include "gbcpch.h"
#include "LayerStack.h"

namespace gbc
{
	LayerStack::LayerStack()
		: layerInsertIndex(0) {}

	LayerStack::~LayerStack()
	{
		for (Layer *layer : layers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer *layer)
	{
		layers.emplace(layers.begin() + layerInsertIndex++, layer);
		layer->onAttach();
	}

	void LayerStack::pushOverlay(Layer *overlay)
	{
		layers.emplace_back(overlay);
		overlay->onAttach();
	}

	void LayerStack::popLayer(Layer *layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end())
		{
			layers.erase(it);
			--layerInsertIndex;
			layer->onDetach();
		}
	}

	void LayerStack::popOverlay(Layer *overlay)
	{
		auto it = std::find(layers.begin(), layers.end(), overlay);
		if (it != layers.end())
		{
			layers.erase(it);
			overlay->onDetach();
		}
	}

	void LayerStack::onUpdate()
	{
		for (Layer *layer : layers)
			layer->onUpdate();
	}

	bool LayerStack::onEvent(Event &e)
	{
		for (auto it = layers.end(); it != layers.begin();)
		{
			(*--it)->onEvent(e);
			if (e.isHandled())
				return true;
		}
		return false;
	}
}
