#pragma once

#include "Event.h"

namespace gbc
{
	class PathDropEvent : public Event
	{
	public:
		PathDropEvent(int pathCount, const char** paths)
			: pathCount(pathCount)
		{
			this->paths.reserve(pathCount);
			for (int i = 0; i < pathCount; i++)
				this->paths.emplace_back(paths[i]);
		}
		EVENT_CATEGORY(EventCategory_None)
		EVENT_TYPE(PathDrop)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Path Drop Event: pathCount=" << pathCount << " paths=[ ";
			for (const auto& path : paths)
				ss << "\"" << path << "\" ";
			ss << ']';
			return ss.str();
		}
#endif
		inline int getPathCount() const { return pathCount; }
		inline const std::vector<std::string>& getPaths() const { return paths; }
	private:
		int pathCount;
		std::vector<std::string> paths;
	};
}
