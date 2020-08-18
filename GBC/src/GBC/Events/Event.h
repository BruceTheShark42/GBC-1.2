#pragma once

#include "gbcpch.h"
#include "GBC/Core/core.h"

namespace gbc
{
	enum class EventType
	{
		None,
		WindowClosed, WindowResized, WindowMoved, WindowGainedFocus, WindowLostFocus,
			WindowMinimized, WindowUnminimized, WindowMaximized, WindowUnmaximized,
		KeyPressed, KeyTyped, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, MouseEntered, MouseExited
	};

	enum EventCategory
	{
		EventCategoryNone,
		EventCategoryWindow      = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	#define EVENT_TYPE(type) static EventType getStaticType() { return EventType::type; }\
						 virtual EventType getType() const override { return EventType::type; }
	#define EVENT_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual EventType getType() const = 0;
		virtual int getCategoryFlags() const = 0;
		inline bool isInCategory(EventCategory category) const { return getCategoryFlags()&  category; }
		inline bool isHandled() const { return handled; }
		inline void setHandled(bool handled) { this->handled = handled; }
#ifdef GBC_DEBUG
		virtual std::string toString() const = 0;
#endif
	private:
		friend class EventDispatcher;
		bool handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			: e(e) {}

		template<typename T>
		bool dispatch(std::function<bool(T&)> func)
		{
			if (!e.isHandled() && e.getType() == T::getStaticType())
			{
				if (func(*(T*)&e))
					e.handled = true;
				return true;
			}
			return false;
		}
	private:
		Event& e;
	};

	inline std::ostream& operator<<(std::ostream& ostr, const Event& e)
	{
#ifdef GBC_DEBUG
		return ostr << e.toString();
#else
		return ostr;
#endif
	}
}
