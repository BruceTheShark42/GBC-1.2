#pragma once

#include "Event.h"

namespace gbc
{
	class WindowClosedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowClosed)
		std::string toString() const override
		{
			return "Window Closed Event";
		}
	};

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(int width, int height)
			: width(width), height(height) {}
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowResized)
		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Resized Event: width=" << width << ", height=" << height;
			return ss.str();
		}
	private:
		int width, height;
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(int x, int y)
			: x(x), y(y) {}
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowMoved)
		inline int getX() const { return x; }
		inline int getY() const { return y; }
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Moved Event: x=" << x << ", y=" << y;
			return ss.str();
		}
	private:
		int x, y;
	};

	class WindowGainedFocusEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowGainedFocus)
		std::string toString() const override
		{
			return "Window Gained Focus Event";
		}
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowLostFocus)
		std::string toString() const override
		{
			return "Window Lost Focus Event";
		}
	};

	class WindowMinimizedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowMinimized)
		std::string toString() const override
		{
			return "Window Minimized Event";
		}
	};

	class WindowUnminimizedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowUnminimized)
		std::string toString() const override
		{
			return "Window Unminimized Event";
		}
	};

	class WindowMaximizedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowMaximized)
		std::string toString() const override
		{
			return "Window Maximized Event";
		}
	};

	class WindowUnmaximizedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowUnmaximized)
		std::string toString() const override
		{
			return "Window Unmaximized Event";
		}
	};
}
