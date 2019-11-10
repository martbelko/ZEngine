#pragma once

#include "zpch.hpp"
#include "ZEngine/Core/Core.hpp"

namespace ZEngine {

#define EVENT_TYPE(type) static Event::Type getStaticType() { return Event::Type::type; }\
						 virtual Event::Type getEventType() const override { return getStaticType(); }\
						 virtual std::string getName() const override { return #type; }

	class Event
	{
	public:
		enum class Type
		{
			None = 0,
			WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
			AppTick, AppUpdate, AppRender,
			KeyPressed, KeyReleased, KeyTyped,
			MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
		};

		virtual Event::Type getEventType() const = 0;
		virtual std::string getName() const = 0;
		virtual std::string toString() const = 0;

		bool Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) { }

		template<typename T, typename F>
		bool dispatch(const F& func)
		{
			if (T::getStaticType() == m_Event.getEventType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& out, const Event& event)
	{
		return out << event.toString();
	}

}
