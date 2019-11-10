#pragma once

#include "ZEngine/Events/Event.hpp"

namespace ZEngine {

	class Layer
	{
	public:
		// TODO: Debug name only in debug mode
		Layer(const std::string& debugName);
		virtual ~Layer() = default;

		virtual void onAttach() { }
		virtual void onDetach() { }
		virtual void onUpdate() { }
		virtual void onEvent(Event& event) { }
		virtual void onImGuiRender() { }

		inline const std::string& getDebugName() const { return m_strDebugName; }
	private:
		std::string m_strDebugName;
	};

}
