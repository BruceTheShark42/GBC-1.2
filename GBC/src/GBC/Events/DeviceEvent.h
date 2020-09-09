#pragma once

#include "Event.h"

namespace gbc
{
	class DeviceConnectEvent : public Event
	{
	protected:
		DeviceConnectEvent(bool connect)
			: connect(connect) {}
		EVENT_CATEGORY(EventCategory_Device)
		inline bool isConnected() const { return connect; }
	protected:
		bool connect;
	};

	class DeviceJoystickConnectEvent : public DeviceConnectEvent
	{
	public:
		DeviceJoystickConnectEvent(bool connect, int id)
			: DeviceConnectEvent(connect), id(id) {}
		EVENT_TYPE(DeviceJoystickConnect)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Device Joystick Connect Event: connect=" << connect << " id=" << id;
			return ss.str();
		}
#endif
	private:
		int id;
	};
	
	class DeviceMonitorConnectEvent : public DeviceConnectEvent
	{
	public:
		DeviceMonitorConnectEvent(bool connect, void* nativeMonitor)
			: DeviceConnectEvent(connect), nativeMonitor(nativeMonitor) {}
		EVENT_TYPE(DeviceMonitorConnect)
#ifdef GBC_DEBUG
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Device Monitor Connect Event: connect=" << connect << " nativeMonitor=" << nativeMonitor;
			return ss.str();
		}
#endif
	private:
		void* nativeMonitor;
	};
}
