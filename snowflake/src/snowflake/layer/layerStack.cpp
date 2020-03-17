#include <sfpch.h>
#include "layerStack.h"

namespace SF {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
	
		for each (auto layer in this->m_Layers) {

			delete layer;

		}
	
	}

	void LayerStack::pushLayer(Layer* layer)
	{

		this->m_Layers.emplace(m_Layers.begin() + this->m_LayerInsertIndex, layer);
		this->m_LayerInsertIndex++;
		layer->onAttach();

	}

	void LayerStack::pushOverlay(Layer* overlay)
	{

		m_Layers.emplace_back(overlay);
		overlay->onAttach();

	}

	void LayerStack::popLayer(Layer* layer)
	{

		std::vector<Layer*>::iterator it = std::find(this->m_Layers.begin(), this->m_Layers.begin() + this->m_LayerInsertIndex, layer);
		
		if (it != this->m_Layers.begin() + this->m_LayerInsertIndex) {

			layer->onDetach();
			this->m_Layers.erase(it);
			this->m_LayerInsertIndex++;

		}

	}

	void LayerStack::popOverlay(Layer* overlay)
	{

		std::vector<Layer*>::iterator it = std::find(this->m_Layers.begin(), this->m_Layers.begin() + this->m_LayerInsertIndex, overlay);

		if (it != this->m_Layers.begin() + this->m_LayerInsertIndex) {

			overlay->onDetach();
			this->m_Layers.erase(it);

		}

	}

	std::vector<Layer*>::iterator LayerStack::begin()
	{
		return this->m_Layers.begin();
	}

	std::vector<Layer*>::iterator LayerStack::end()
	{
		return this->m_Layers.end();
	}



}