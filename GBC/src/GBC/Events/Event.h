#pragma once

#include "gbcpch.h"
#include "GBC/Core/core.h"

namespace gbc
{
	enum class EventType
	{
		None,
		WindowClose, WindowResize, WindowMove, WindowFocus, WindowMinimize, WindowMaximize,
			WindowFramebufferResize, WindowContentScale, WindowRefresh,
		KeyPress, KeyRelease, KeyChar, KeyCharMods,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll, MouseEnter,
		DeviceJoystickConnect, DeviceMonitorConnect,
		PathDrop
	};

	enum EventCategory
	{
		EventCategory_None,
		EventCategory_Window      = BIT(0),
		EventCategory_Input       = BIT(1),
		EventCategory_Keyboard    = BIT(2),
		EventCategory_KeyChar     = BIT(3),
		EventCategory_Mouse       = BIT(4),
		EventCategory_MouseButton = BIT(5),
		EventCategory_Device      = BIT(6)
	};

	enum EventKeyMods
	{
		EventKeyMods_None,
		EventKeyMods_Shift    = BIT(0),
		EventKeyMods_Ctrl     = BIT(1),
		EventKeyMods_Alt      = BIT(2),
		EventKeyMods_Super    = BIT(3),
		EventKeyMods_CapsLock = BIT(4),
		EventKeyMods_NumLock  = BIT(5),
	};

	#define EVENT_TYPE(type) static EventType getStaticType() { return EventType::type; }\
						 virtual EventType getType() const override { return EventType::type; }
	#define EVENT_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual EventType getType() const = 0;
		virtual int getCategoryFlags() const = 0;
		inline bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; }
#ifdef GBC_DEBUG
		virtual std::string toString() const = 0;
#endif
		bool handled = false;
	private:
		friend class EventDispatcher;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: event(event) {}

		template<typename T>
		bool dispatch(std::function<bool(T&)> func)
		{
			if (!event.handled && event.getType() == T::getStaticType())
			{
				if (func(*(T*)&event))
					event.handled = true;
				return true;
			}
			return false;
		}
	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& ostr, const Event& event)
	{
#ifdef GBC_DEBUG
		return ostr << event.toString();
#else
		return ostr;
#endif
	}
}
