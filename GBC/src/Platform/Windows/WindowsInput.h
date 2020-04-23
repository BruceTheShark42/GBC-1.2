#pragma once

#include "GBC/Core/core.h"
#include "GBC/Core/Input.h"

namespace gbc
{
	class WindowsInput : public Input
	{
	public:
		virtual bool isKeyPressedImpl(int keyCode) override;
		virtual bool isKeyReleasedImpl(int keyCode) override;

		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual bool isMouseButtonReleasedImpl(int button) override;

		virtual std::pair<float, float> getMousePosImpl() override;
		virtual float getMousePosXImpl() override;
		virtual float getMousePosYImpl() override;
	};
}
