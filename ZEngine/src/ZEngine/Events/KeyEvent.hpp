#pragma once

#include "Event.hpp"

namespace ZEngine {

	class KeyEvent : public Event
	{
	public:
		inline int getKeycode() const { return m_iKeycode; }
	protected:
		KeyEvent(int keycode)
			: m_iKeycode(keycode) { }

		int m_iKeycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, unsigned int repeatCount)
			: KeyEvent(keycode), m_uiRepeatCount(repeatCount) { }

		inline unsigned int getRepeatCount() const { return m_uiRepeatCount; }

		virtual std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_iKeycode << " ( " << m_uiRepeatCount << " repeats )";
			return ss.str();
		}

		EVENT_TYPE(KeyPressed)
	private:
		unsigned int m_uiRepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) { }

		virtual std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_iKeycode;
			return ss.str();
		}

		EVENT_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) { }

		virtual std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_iKeycode;
			return ss.str();
		}

		EVENT_TYPE(KeyTyped)
	};

}