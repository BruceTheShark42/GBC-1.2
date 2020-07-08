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
		EVENT_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)
		inline MouseCode getButton() const { return button; }
	protected:
		MouseCode button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button)
			: MouseButtonEvent(button) {}
		EVENT_TYPE(MouseButtonPressed)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Pressed Event: button=" << button;
			return ss.str();
		}
#endif
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button)
			: MouseButtonEvent(button) {}
		EVENT_TYPE(MouseButtonReleased)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Released Event: button=" << button;
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
		EVENT_CATEGORY(EventCategoryInput | EventCategoryMouse)
		inline float getX() const { return x; }
		inline float getY() const { return y; }
	protected:
		float x, y;
	};

	class MouseMovedEvent : public MousePositionEvent
	{
	public:
		MouseMovedEvent(float x, float y)
			: MousePositionEvent(x, y) {}
		EVENT_TYPE(MouseMoved)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Moved Event: x=" << x << ", y=" << y;
			return ss.str();
		}
#endif
	};

	class MouseScrolledEvent : public MousePositionEvent
	{
	public:
		MouseScrolledEvent(float x, float y)
			: MousePositionEvent(x, y) {}
		EVENT_TYPE(MouseScrolled)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled Event: x=" << x << ", y=" << y;
			return ss.str();
		}
#endif
	};

	class MouseEnteredEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(MouseEntered)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Mouse Entered Event";
		}
#endif
	};

	class MouseExitedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(MouseExited)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Mouse Exited Event";
		}
#endif
	};
}
