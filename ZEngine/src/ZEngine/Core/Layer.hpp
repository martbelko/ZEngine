#pragma once

#include "ZEngine/Events/Event.hpp"

#include "ZEngine/Core/Timestep.hpp"

namespace ZEngine {

	class Layer
	{
	public:
		// TODO: Debug name only in debug mode
		Layer(const std::string& debugName);
		virtual ~Layer() = default;

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate(const Timestep& ts) { }
		virtual void OnEvent(Event& event) { }
		virtual void OnImGuiRender() { }

		inline const std::string& GetDebugName() const { return m_strDebugName; }
	private:
		std::string m_strDebugName;
	};

}
