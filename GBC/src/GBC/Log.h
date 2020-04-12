#pragma once

#include "core.h"
#include <spdlog/spdlog.h>

namespace gbc
{
	class GBC_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

// Core log macros
#define GBC_CORE_TRACE(...) gbc::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GBC_CORE_INFO(...) gbc::Log::getCoreLogger()->info(__VA_ARGS__)
#define GBC_CORE_WARN(...) gbc::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GBC_CORE_ERROR(...) gbc::Log::getCoreLogger()->error(__VA_ARGS__)
#define GBC_CORE_FATAL(...) gbc::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define GBC_TRACE(...) gbc::Log::getClientLogger()->trace(__VA_ARGS__)
#define GBC_INFO(...) gbc::Log::getClientLogger()->info(__VA_ARGS__)
#define GBC_WARN(...) gbc::Log::getClientLogger()->warn(__VA_ARGS__)
#define GBC_ERROR(...) gbc::Log::getClientLogger()->error(__VA_ARGS__)
#define GBC_FATAL(...) gbc::Log::getClientLogger()->fatal(__VA_ARGS__)
