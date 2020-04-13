#pragma once

#include "Event.h"

namespace gbc
{
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int keyCode)
			: keyCode(keyCode) {}
	public:
		EVENT_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
		inline int getKeyCode() const { return keyCode; }
	protected:
		int keyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, bool repeat)
			: KeyEvent(keyCode), repeat(repeat) {}
		EVENT_TYPE(KeyPressed)
		inline bool hasRepeated() const { return repeat; }
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed Event: keyCode=" << keyCode << ", repeat=" << repeat;
			return ss.str();
		}
	private:
		bool repeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode) {}
		EVENT_TYPE(KeyReleased)
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Released Event: keyCode=" << keyCode;
			return ss.str();
		}
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode) {}
		EVENT_TYPE(KeyTyped)
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Typed Event: keyCode=" << keyCode;
			return ss.str();
		}
	};
}
