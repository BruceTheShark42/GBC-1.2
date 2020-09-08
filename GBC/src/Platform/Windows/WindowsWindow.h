#pragma once

#include "GBC/Core/Window.h"
#include <GLFW/glfw3.h>
#include "GBC/Renderer/GraphicsContext.h"

namespace gbc
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;
		virtual float getElapsedTime() const override;

		inline int getWidth() const override { return state.current.width; }
		inline int getHeight() const override { return state.current.height; }

		virtual const char* getTitle() const override { return state.title; }
		virtual void setTitle(const char* title) override;

		inline virtual bool getVSync() const override { return state.vsync; }
		virtual void setVSync(bool enabled) override;

		inline virtual bool getCaptureMouse() const override { return state.captureMouse; }
		virtual void setCaptureMouse(bool enabled) override;

		inline virtual bool getResizable() const override { return state.resizable; }
		virtual void setResizable(bool enabled) override;

		inline virtual bool getFullscreen() const override { return state.fullscreen; }
		virtual void setFullscreen(bool enabled) override;
		
		inline virtual void setEventCallback(const EventCallbackFunc& callback) override { state.callback = callback; }
		inline virtual void* getNativeWindow() const override { return window; };
	private:
		void saveDimensions();

		GLFWwindow* window;
		GraphicsContext* context;

		struct WindowState
		{
			struct
			{
				int x = 0;
				int y = 0;
				int width = 0;
				int height = 0;
			} current, previous;

			const char* title = nullptr;
			bool vsync = false;
			bool captureMouse = false;
			bool resizable = true;
			bool fullscreen = false;
			bool adaptiveSize = false;

			EventCallbackFunc callback;
		} state;

		mutable float lastTime = 0.0f;
	};
}
