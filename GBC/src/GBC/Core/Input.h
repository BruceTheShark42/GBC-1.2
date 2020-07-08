#pragma once

#include "core.h"
#include "keyCodes.h"
#include "mouseButtons.h"

namespace gbc
{
	class Input
	{
	public:
		static bool isKeyPressed(int keyCode);
		static bool isKeyReleased(int keyCode);

		static bool isMouseButtonPressed(int button);
		static bool isMouseButtonReleased(int button);

		static std::pair<float, float> getMousePos();
		static float getMousePosX();
		static float getMousePosY();
	};
}
