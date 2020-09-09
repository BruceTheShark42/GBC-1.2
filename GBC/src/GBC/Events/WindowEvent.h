#pragma once

#include "Event.h"

namespace gbc
{
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(WindowClose)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Window Close Event";
		}
#endif
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: width(width), height(height) {}
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(WindowResize)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Resize Event: width=" << width << " height=" << height;
			return ss.str();
		}
#endif
		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
	private:
		int width;
		int height;
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(int x, int y)
			: x(x), y(y) {}
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(WindowMove)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Move Event: x=" << x << " y=" << y;
			return ss.str();
		}
#endif
		inline int getX() const { return x; }
		inline int getY() const { return y; }
	private:
		int x;
		int y;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(bool focus)
			: focus(focus) {}
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(WindowFocus)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Focus Event: focus=" << focus;
			return ss.str();
		}
#endif
		bool isFocused() const { return focus; }
	private:
		bool focus;
	};

	class WindowMinimizeEvent : public Event
	{
	public:
		WindowMinimizeEvent(bool minimize)
			: minimize(minimize) {}
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(WindowMinimize)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Minimize Event: minimize=" << minimize;
			return ss.str();
		}
#endif
		bool isMinimized() const { return minimize; }
	private:
		bool minimize;
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		WindowMaximizeEvent(bool maximize)
			: maximize(maximize) {}
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(WindowMaximize)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Maximized Event: maximize=" << maximize;
			return ss.str();
		}
#endif
		bool isMaximized() const { return maximize; }
	private:
		bool maximize;
	};

	class WindowFramebufferResizeEvent : public Event
	{
	public:
		WindowFramebufferResizeEvent(int width, int height)
			: width(width), height(height) {}
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(WindowFramebufferResize)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Framebuffer Resize Event: width=" << width << " height=" << height;
			return ss.str();
		}
#endif
		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
	private:
		int width;
		int height;
	};

	class WindowContentScaleEvent : public Event
	{
	public:
		WindowContentScaleEvent(float scaleX, float scaleY)
			: scaleX(scaleX), scaleY(scaleX) {}
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(WindowContentScale)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Window Content Scale Event: scaleX=" << scaleX << " scaleY=" << scaleY;
			return ss.str();
		}
#endif
		inline float getScaleX() const { return scaleX; }
		inline float getScaleY() const { return scaleY; }
	private:
		float scaleX;
		float scaleY;
	};

	class WindowRefreshEvent : public Event
	{
	public:
		EVENT_CATEGORY(EventCategory_Window)
		EVENT_TYPE(WindowRefresh)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			return "Window Refresh Event";
		}
#endif
	};
}
