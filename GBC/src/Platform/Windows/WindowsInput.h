#pragma once

#include "GBC/core.h"
#include "GBC/Input.h"

namespace gbc
{
	class GBC_API WindowsInput : public Input
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
