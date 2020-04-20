#pragma once

#include "Event.h"

namespace gbc
{
	class WindowClosedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowClosed)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Window Closed Event";
		}
#endif
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
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Resized Event: width=" << width << ", height=" << height;
			return ss.str();
		}
#endif
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
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Moved Event: x=" << x << ", y=" << y;
			return ss.str();
		}
#endif
	private:
		int x, y;
	};

	class WindowGainedFocusEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowGainedFocus)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Window Gained Focus Event";
		}
#endif
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowLostFocus)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Window Lost Focus Event";
		}
#endif
	};

	class WindowMinimizedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowMinimized)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Window Minimized Event";
		}
#endif
	};

	class WindowUnminimizedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowUnminimized)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Window Unminimized Event";
		}
#endif
	};

	class WindowMaximizedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowMaximized)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Window Maximized Event";
		}
#endif
	};

	class WindowUnmaximizedEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategoryWindow)
		EVENT_TYPE(WindowUnmaximized)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Window Unmaximized Event";
		}
#endif
	};
}
