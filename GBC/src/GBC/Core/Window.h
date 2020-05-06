#pragma once

#include "core.h"
#include "GBC/Events/Event.h"

namespace gbc
{
	struct WindowProps
	{
		std::string title;
		unsigned int width, height;
		bool resizable, fullscreen, vsync, cursorEnabled;

		WindowProps(std::string title = "GBC Engine",
			unsigned int width = 1280, unsigned int height = 720,
			bool resizable = true, bool fullscreen = false,
			bool vsync = true, bool cursorEnabled = true)
			: title(title), width(width), height(height),
			resizable(resizable), fullscreen(fullscreen),
			vsync(vsync), cursorEnabled(cursorEnabled) {}
	};

	class Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallback(const EventCallbackFunc &callback) = 0;

		virtual void setFullscreen(bool enabled) = 0;
		virtual bool getFullscreen() const = 0;
		inline void toggleFullscreen() { setFullscreen(!getFullscreen()); };

		virtual void setVSync(bool enabled) = 0;
		virtual bool getVSync() const = 0;
		inline void toggleVSync() { setVSync(!getVSync()); };

		virtual void setCursorEnabled(bool enabled) = 0;
		virtual bool getCursorEnabled() const = 0;
		inline void toggleCursorEnabled() { setCursorEnabled(!getCursorEnabled()); };

		virtual void* getNativeWindow() const = 0;
		static Scope<Window> create(const WindowProps &props = WindowProps());
	};
}