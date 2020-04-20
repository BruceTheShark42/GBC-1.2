#pragma once

#include "gbcpch.h"
#include "core.h"

namespace gbc
{
	class Input
	{
	public:
		inline static bool isKeyPressed(int keyCode) { return instance->isKeyPressedImpl(keyCode); }
		inline static bool isKeyReleased(int keyCode) { return instance->isKeyReleasedImpl(keyCode); }

		inline static bool isMouseButtonPressed(int button) { return instance->isMouseButtonPressedImpl(button); }
		inline static bool isMouseButtonReleased(int button) { return instance->isMouseButtonReleasedImpl(button); }

		inline static std::pair<float, float> getMousePos() { return instance->getMousePosImpl(); }
		inline static float getMousePosX() { return instance->getMousePosXImpl(); }
		inline static float getMousePosY() { return instance->getMousePosYImpl(); }
	protected:
		virtual bool isKeyPressedImpl(int keyCode) = 0;
		virtual bool isKeyReleasedImpl(int keyCode) = 0;

		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual bool isMouseButtonReleasedImpl(int button) = 0;

		virtual std::pair<float, float> getMousePosImpl() = 0;
		virtual float getMousePosXImpl() = 0;
		virtual float getMousePosYImpl() = 0;
	private:
		static Input *instance;
	};
}
