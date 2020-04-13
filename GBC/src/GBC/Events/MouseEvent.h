#pragma once

#include "Event.h"

namespace gbc
{
	class MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(int button)
			: button(button) {}
	public:
		EVENT_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)
		inline int getButton() const { return button; }
	protected:
		int button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}
		EVENT_TYPE(MouseButtonPressed)
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Pressed Event: button=" << button;
			return ss.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}
		EVENT_TYPE(MouseButtonReleased)
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Released Event: button=" << button;
			return ss.str();
		}
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
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Moved Event: x=" << x << ", y=" << y;
			return ss.str();
		}
	};

	class MouseScrolledEvent : public MousePositionEvent
	{
	public:
		MouseScrolledEvent(float x, float y)
			: MousePositionEvent(x, y) {}
		EVENT_TYPE(MouseScrolled)
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled Event: x=" << x << ", y=" << y;
			return ss.str();
		}
	};

	class MouseEnteredEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(MouseEntered)
		std::string toString() const override
		{
			return "Mouse Entered Event";
		}
	};

	class MouseExitedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(MouseExited)
		std::string toString() const override
		{
			return "Mouse Exited Event";
		}
	};
}
