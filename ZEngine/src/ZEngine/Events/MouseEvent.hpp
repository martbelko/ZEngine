#pragma once

#include "Event.hpp"

namespace ZEngine {

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button)
			: m_iButton(button) { }

		inline int getButton() const { return m_iButton; }
	protected:
		int m_iButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) { }

		virtual std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_iButton;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) { }

		virtual std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_iButton;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonReleased)
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float xpos, float ypos)
			: m_fXPos(xpos), m_fYPos(ypos) { }

		inline float GetX() const { return m_fXPos; }
		inline float GetY() const { return m_fYPos; }

		virtual std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: ( " << m_fXPos << " ; " << m_fYPos << " )";
			return ss.str();
		}

		EVENT_TYPE(MouseMoved)
	private:
		float m_fYPos, m_fXPos;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_fXOffset(xOffset), m_fYOffset(yOffset) { }

		inline float getXOffset() const { return m_fXOffset; }
		inline float getYOffset() const { return m_fYOffset; }

		virtual std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: ( " << m_fXOffset << " ; " << m_fYOffset << " )";
			return ss.str();
		}

		EVENT_TYPE(MouseScrolled)
	private:
		float m_fXOffset, m_fYOffset;
	};

}
