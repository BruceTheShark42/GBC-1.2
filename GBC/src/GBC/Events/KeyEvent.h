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
		EVENT_CATEGORY(EventCategory_Input | EventCategory_Keyboard)
		inline KeyCode getKeyCode() const { return keyCode; }
	protected:
		KeyCode keyCode;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(KeyCode keyCode, bool repeat)
			: KeyEvent(keyCode), repeat(repeat) {}
		EVENT_TYPE(KeyPress)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Press Event: keyCode=" << keyCode << " repeat=" << repeat;
			return ss.str();
		}
#endif
		inline bool hasRepeated() const { return repeat; }
	private:
		bool repeat;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(KeyCode keyCode)
			: KeyEvent(keyCode) {}
		EVENT_TYPE(KeyRelease)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Release Event: keyCode=" << keyCode;
			return ss.str();
		}
#endif
	};

	class KeyCharEvent : public Event
	{
	public:
		KeyCharEvent(unsigned int codepoint)
			: codepoint(codepoint) {}
		EVENT_CATEGORY(EventCategory_Input | EventCategory_Keyboard | EventCategory_KeyChar)
		EVENT_TYPE(KeyChar)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Char Event: codepoint=" << codepoint;
			return ss.str();
		}
#endif
		inline unsigned int getCodepoint() const { return codepoint; }
	private:
		unsigned int codepoint;
	};

	class KeyCharModsEvent : public Event
	{
	public:
		KeyCharModsEvent(unsigned int codepoint, int mods)
			: codepoint(codepoint), mods(mods) {}
		EVENT_CATEGORY(EventCategory_Input | EventCategory_Keyboard | EventCategory_KeyChar)
		EVENT_TYPE(KeyCharMods)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Char Mods Event: codepoint=" << codepoint << " mods=" << mods;
			return ss.str();
		}
#endif
		inline unsigned int getCodepoint() const { return codepoint; }
		inline int getMods() const { return mods; }
		inline bool getMod(EventKeyMods mask) const { return mods & mask; }
	private:
		unsigned int codepoint;
		int mods;
	};
}
