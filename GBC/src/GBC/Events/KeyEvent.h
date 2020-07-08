#pragma once

#include "Event.h"
#include "GBC/Core/keyCodes.h"

namespace gbc
{
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(KeyCode keyCode)
			: keyCode(keyCode) {}
	public:
		EVENT_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
		inline KeyCode getKeyCode() const { return keyCode; }
	protected:
		KeyCode keyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keyCode, bool repeat)
			: KeyEvent(keyCode), repeat(repeat) {}
		EVENT_TYPE(KeyPressed)
		inline bool hasRepeated() const { return repeat; }
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed Event: keyCode=" << keyCode << ", repeat=" << repeat;
			return ss.str();
		}
#endif
	private:
		bool repeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keyCode)
			: KeyEvent(keyCode) {}
		EVENT_TYPE(KeyReleased)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Released Event: keyCode=" << keyCode;
			return ss.str();
		}
#endif
	};

	class KeyTypedEvent : public Event
	{
	public:
		KeyTypedEvent(unsigned int unicode)
			: unicode(unicode) {}
		EVENT_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
		EVENT_TYPE(KeyTyped)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Typed Event: unicode=" << unicode;
			return ss.str();
		}
		inline unsigned int getUnicode() const { return unicode; }
	protected:
		unsigned int unicode;
#endif
	};
}
