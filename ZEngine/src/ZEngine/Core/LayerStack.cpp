#include "zpch.hpp"
#include "LayerStack.hpp"

namespace ZEngine {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->onDetach();
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_uiInsertionIndex++, layer);
	}

	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_uiInsertionIndex, layer);
		if (it != m_Layers.begin() + m_uiInsertionIndex)
		{
			layer->onDetach();
			m_Layers.erase(it);
			--m_uiInsertionIndex;
		}
	}

	void LayerStack::pushOverlay(Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerStack::popOverlay(Layer* layer)
	{
		auto it = std::find(m_Layers.begin() + m_uiInsertionIndex, m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->onDetach();
			m_Layers.erase(it);
		}
	}

}