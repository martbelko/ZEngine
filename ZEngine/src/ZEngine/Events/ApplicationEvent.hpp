#pragma once

#include "Event.hpp"

namespace ZEngine {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int lastWidth, unsigned int lastHeight, unsigned int newWidth, unsigned int newHeight)
			: m_uiLastWidth(lastWidth), m_uiLastHeight(lastHeight), m_uiNewWidth(newWidth), m_uiNewHeight(newHeight) { }

		inline unsigned int getLastWidth() const { return m_uiLastWidth; }
		inline unsigned int getLastHeight() const { return m_uiLastHeight; }
		inline unsigned int getNewWidth() const { return m_uiNewWidth; }
		inline unsigned int getNewHeight() const { return m_uiNewHeight; }

		virtual std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResize: ( " << m_uiLastWidth << " ; " << m_uiLastHeight << " ) --> ( " << m_uiNewWidth << " ; " << m_uiNewHeight << " )";
			return ss.str();
		}

		EVENT_TYPE(WindowResize)
	private:
		unsigned int m_uiLastWidth, m_uiLastHeight;
		unsigned int m_uiNewWidth, m_uiNewHeight;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() { }

		std::string toString() const override
		{
			return "WindowCloseEvent";
		}

		EVENT_TYPE(WindowClose)
	};
}
