#pragma once

#include "Events/Event.h"

namespace Engine
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32 width, uint32 height)
			:m_uWidth(width), m_uHeight(height) {}

		inline uint32 GetWidth() const noexcept { return m_uWidth; }
		inline uint32 GetHeight() const noexcept { return m_uHeight; }

		virtual CString ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_uWidth << ", " << m_uHeight;
			return ss.str();
		}

		DEFINE_EVENT_TYPE(WindowResizeEvent)
		DEFINE_EVENT_CATEGORY(EVENT_CATEGORY_APPLICATION)
	private:
		uint32 m_uWidth, m_uHeight;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		DEFINE_EVENT_TYPE(WindowCloseEvent)
		DEFINE_EVENT_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};
}