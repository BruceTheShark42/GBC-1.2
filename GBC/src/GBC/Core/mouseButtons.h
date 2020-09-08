#pragma once

namespace gbc
{
	enum class MouseCode : unsigned short
	{
		// Taken from glfw3.h and modified
		MB1       = 0, MBLeft    = MB1,
		MB2       = 1, MBRight   = MB2,
		MB3       = 2, MBMiddle  = MB3,
		MB4       = 3,
		MB5       = 4,
		MB6       = 5,
		MB7       = 6,
		MB8       = 7,
		
		Count
	};

	inline std::ostream& operator<<(std::ostream& ostr, MouseCode button)
	{
		return ostr << static_cast<unsigned short>(button);
	}
}
