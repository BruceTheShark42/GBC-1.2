#pragma once

namespace gbc
{
	enum class MouseCode : unsigned short
	{
		// Taken from glfw3.h and modified
		MB1       = 0,
		MB2       = 1,
		MB3       = 2,
		MB4       = 3,
		MB5       = 4,
		MB6       = 5,
		MB7       = 6,
		MB8       = 7,
		MBLast    = MB8,
		MBLeft    = MB1,
		MBRight   = MB2,
		MBMiddle  = MB3
	};

	inline std::ostream& operator<<(std::ostream &ostr, MouseCode button)
	{
		return ostr << static_cast<unsigned short>(button);
	}
}
