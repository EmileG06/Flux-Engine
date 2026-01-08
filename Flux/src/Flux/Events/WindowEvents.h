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
		WindowResizedEvent(float width, float height)
			: m_Width(width), m_Height(height) {
		}

		float GetWidth() const { return m_Width; }
		float GetHeight() const { return m_Height; }

		virtual std::string ToString() const override
		{
			return std::format("WindowResizedEvent: {0}, {1}", GetWidth(), GetHeight());
		}

		EVENT_CLASS_TYPE(WindowResized);
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		float m_Width;
		float m_Height;
	};

}
