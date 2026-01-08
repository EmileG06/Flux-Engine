#pragma once

#include "Event.h"

#include <format>

namespace Flux {

	class MouseButtonEvent : public Event
	{
	public:
		int32_t GetButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	protected:
		MouseButtonEvent(int32_t button)
			: m_Button(button) { }

		int32_t m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int32_t button)
			: MouseButtonEvent(button) {
		}

		virtual std::string ToString() const override
		{
			return std::format("MouseButtonPressedEvent: {0})", GetButton());
		}

		EVENT_CLASS_TYPE(MouseButtonPressed);
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int32_t button)
			: MouseButtonEvent(button) {
		}

		virtual std::string ToString() const override
		{
			return std::format("MouseButtonReleasedEvent: {0})", GetButton());
		}

		EVENT_CLASS_TYPE(MouseButtonReleased);
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_X(x), m_Y(y) {
		}

		float GetX() const { return m_X; }
		float GetY() const { return m_Y; }

		virtual std::string ToString() const override
		{
			return std::format("MouseMovedEvent: {0}, {1}", GetX(), GetY());
		}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	private:
		float m_X;
		float m_Y;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			: m_X(x), m_Y(y) {
		}

		float GetX() const { return m_X; }
		float GetY() const { return m_Y; }

		virtual std::string ToString() const override
		{
			return std::format("MouseScrolledEvent: {0}, {1}", GetX(), GetY());
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	private:
		float m_X;
		float m_Y;
	};

}
