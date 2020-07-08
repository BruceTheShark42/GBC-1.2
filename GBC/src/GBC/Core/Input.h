#pragma once

#include "core.h"
#include "keyCodes.h"
#include "mouseButtons.h"

namespace gbc
{
	class Input
	{
	public:
		static bool isKeyPressed(KeyCode keyCode);
		static bool isKeyReleased(KeyCode keyCode);

		static bool isMouseButtonPressed(MouseCode button);
		static bool isMouseButtonReleased(MouseCode button);

		static std::pair<float, float> getMousePos();
		static float getMousePosX();
		static float getMousePosY();
	};
}
