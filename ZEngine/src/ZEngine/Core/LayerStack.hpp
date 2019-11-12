#pragma once

#include "ZEngine/Core/Layer.hpp"

namespace ZEngine {

	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		inline std::deque<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::deque<Layer*>::iterator end()   { return m_Layers.end();   }
	private:
		std::deque<Layer*> m_Layers;
		unsigned int m_uiInsertionIndex = 0;
	};

}
