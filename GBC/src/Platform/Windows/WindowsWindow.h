#pragma once

#include "GBC/Window.h"
#include <GLFW/glfw3.h>
#include "GBC/Renderer/GraphicsContext.h"

namespace gbc
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps &props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline int getWidth() const override { return data.width; }
		inline int getHeight() const override { return data.height; }

		inline virtual void setEventCallback(const EventCallbackFunc &callback) override { data.callback = callback; };

		virtual void setFullscreen(bool enabled) override;
		inline virtual bool getFullscreen() const override { return data.fullscreen; }

		virtual void setVSync(bool enabled) override;
		inline virtual bool getVSync() const override { return data.vsync; }

		virtual void setCursorEnabled(bool enabled) override;
		inline virtual bool getCursorEnabled() const override { return data.cursorEnabled; }

		inline virtual void* getNativeWindow() const override { return window; };
	private:
		GLFWwindow *window;
		GLFWmonitor *monitor;
		const GLFWvidmode *videoMode;
		GraphicsContext *context;

		struct WindowData
		{
			std::string title;
			int x, y, width, height;
			int pX, pY, pWidth, pHeight;
			bool resizable, fullscreen, vsync, cursorEnabled;
			EventCallbackFunc callback;
		} data;
	};
}
