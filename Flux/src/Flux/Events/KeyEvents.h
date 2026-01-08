#pragma once

#include "Event.h"

#include <format>

namespace Flux {

	class KeyEvent : public Event
	{
	public:
		int32_t GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

	protected:
		KeyEvent(int32_t keyCode)
			: m_KeyCode(keyCode) { }

		int32_t m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int32_t keyCode, bool isRepeat)
			: KeyEvent(keyCode), m_IsRepeat(isRepeat) {
		}

		bool IsRepeat() const { return m_IsRepeat; }

		virtual std::string ToString() const override
		{
			return std::format("KeyPressedEvent: {0} (repeat={1})", GetKeyCode(), IsRepeat());
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		bool m_IsRepeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int32_t keyCode)
			: KeyEvent(keyCode) {
		}

		virtual std::string ToString() const override
		{
			return std::format("KeyReleasedEvent: {0})", GetKeyCode());
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};

}
