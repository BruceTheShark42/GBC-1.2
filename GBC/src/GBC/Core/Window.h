#pragma once

#include "core.h"
#include "GBC/Events/Event.h"

namespace gbc
{
	struct WindowProps
	{
		WindowProps(unsigned int width = 1280, unsigned int height = 720, const char* title = "GB4 Engine",
					bool vsync = true, bool captureMouse = false, bool resizable = true,
					bool fullscreen = false, bool adaptiveSize = true)
			: width(width), height(height), title(title), vsync(vsync), captureMouse(captureMouse),
			  resizable(resizable), fullscreen(fullscreen), adaptiveSize(adaptiveSize) {}
		WindowProps(const WindowProps& props)
			: width(props.width), height(props.height), title(props.title), vsync(props.vsync),
			  captureMouse(props.captureMouse), resizable(props.resizable), fullscreen(props.fullscreen),
			  adaptiveSize(props.adaptiveSize) {}

		unsigned int width;
		unsigned int height;
		const char* title;
		bool vsync;
		bool captureMouse;
		bool resizable;
		bool fullscreen;
		bool adaptiveSize;
	};

	class Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void onUpdate() = 0;
		virtual float getElapsedTime() const = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual const char* getTitle() const = 0;
		virtual void setTitle(const char* title) = 0;

		virtual bool getVSync() const = 0;
		virtual void setVSync(bool vsync) = 0;
		inline void toggleVSync() { setVSync(!getVSync()); }

		virtual bool getCaptureMouse() const = 0;
		virtual void setCaptureMouse(bool captureMouse) = 0;
		inline void toggleCaptureMouse() { setCaptureMouse(!getCaptureMouse()); }

		virtual bool getResizable() const = 0;
		virtual void setResizable(bool resizable) = 0;
		inline void toggleResizable() { setResizable(!getResizable()); }

		virtual bool getFullscreen() const = 0;
		virtual void setFullscreen(bool fullscreen) = 0;
		inline void toggleFullscreen() { setFullscreen(!getFullscreen()); }

		virtual bool getAdaptiveSize() const = 0;
		virtual void setAdaptiveSize(bool adaptiveSize) = 0;
		inline void toggleAdaptiveSize() { setAdaptiveSize(!getAdaptiveSize()); }

		virtual void setEventCallback(const EventCallbackFunc& callback) = 0;
		virtual void* getNativeWindow() const = 0;
		static Scope<Window> create(const WindowProps& props);
	};
}
