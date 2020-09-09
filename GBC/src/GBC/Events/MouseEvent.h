#pragma once

#include "Event.h"
#include "GBC/Core/mouseButtons.h"

namespace gbc
{
	class MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(MouseCode button)
			: button(button) {}
	public:
		EVENT_CATEGORY(EventCategory_Input | EventCategory_Mouse | EventCategory_MouseButton)
		inline MouseCode getButton() const { return button; }
	protected:
		MouseCode button;
	};

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(MouseCode button)
			: MouseButtonEvent(button) {}
		EVENT_TYPE(MouseButtonPress)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Press Event: button=" << button;
			return ss.str();
		}
#endif
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(MouseCode button)
			: MouseButtonEvent(button) {}
		EVENT_TYPE(MouseButtonRelease)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Release Event: button=" << button;
			return ss.str();
		}
#endif
	};

	class MousePositionEvent : public Event
	{
	protected:
		MousePositionEvent(float x, float y)
			: x(x), y(y) {}
	public:
		EVENT_CATEGORY(EventCategory_Input | EventCategory_Mouse)
		inline float getX() const { return x; }
		inline float getY() const { return y; }
	protected:
		float x, y;
	};

	class MouseMoveEvent : public MousePositionEvent
	{
	public:
		MouseMoveEvent(float x, float y)
			: MousePositionEvent(x, y) {}
		EVENT_TYPE(MouseMove)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Move Event: x=" << x << " y=" << y;
			return ss.str();
		}
#endif
	};

	class MouseScrollEvent : public MousePositionEvent
	{
	public:
		MouseScrollEvent(float x, float y)
			: MousePositionEvent(x, y) {}
		EVENT_TYPE(MouseScroll)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scroll Event: xOff=" << x << " yOff=" << y;
			return ss.str();
		}
#endif
	};

	class MouseEnterEvent : public Event
	{
	public:
		MouseEnterEvent(bool enter)
			: enter(enter) {}
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(MouseEnter)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Enter Event: enter=" << enter;
			return ss.str();
		}
#endif
		inline bool hasEntered() const { return enter; }
	private:
		bool enter;
	};
}
