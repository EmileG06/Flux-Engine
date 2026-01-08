#pragma once

#include "Event.h"

#include <format>

namespace Flux {

	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() {}

		EVENT_CLASS_TYPE(WindowClosed);
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {
		}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		virtual std::string ToString() const override
		{
			return std::format("WindowResizedEvent: {0}, {1}", GetWidth(), GetHeight());
		}

		EVENT_CLASS_TYPE(WindowResized);
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

}
