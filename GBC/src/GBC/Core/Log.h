#pragma once

#include "core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace gbc
{
	class Log
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

#ifdef GBC_ENABLE_LOGGING
	// Core log macros
	#define GBC_CORE_TRACE(...) ::gbc::Log::getCoreLogger()->trace(__VA_ARGS__)
	#define GBC_CORE_DEBUG(...) ::gbc::Log::getCoreLogger()->debug(__VA_ARGS__)
	#define GBC_CORE_INFO(...)  ::gbc::Log::getCoreLogger()->info(__VA_ARGS__)
	#define GBC_CORE_WARN(...)  ::gbc::Log::getCoreLogger()->warn(__VA_ARGS__)
	#define GBC_CORE_ERROR(...) ::gbc::Log::getCoreLogger()->error(__VA_ARGS__)
	#define GBC_CORE_FATAL(...) ::gbc::Log::getCoreLogger()->critical(__VA_ARGS__)

	// Client log macros
	#define GBC_CLIENT_TRACE(...) ::gbc::Log::getClientLogger()->trace(__VA_ARGS__)
	#define GBC_CLIENT_DEBUG(...) ::gbc::Log::getClientLogger()->debug(__VA_ARGS__)
	#define GBC_CLIENT_INFO(...)  ::gbc::Log::getClientLogger()->info(__VA_ARGS__)
	#define GBC_CLIENT_WARN(...)  ::gbc::Log::getClientLogger()->warn(__VA_ARGS__)
	#define GBC_CLIENT_ERROR(...) ::gbc::Log::getClientLogger()->error(__VA_ARGS__)
	#define GBC_CLIENT_FATAL(...) ::gbc::Log::getClientLogger()->critical(__VA_ARGS__)
#else
	// Core log macros
	#define GBC_CORE_TRACE(...)
	#define GBC_CORE_DEBUG(...)
	#define GBC_CORE_INFO(...)
	#define GBC_CORE_WARN(...)
	#define GBC_CORE_ERROR(...)
	#define GBC_CORE_FATAL(...)

	// Client log macros
	#define GBC_CLIENT_TRACE(...)
	#define GBC_CLIENT_DEBUG(...)
	#define GBC_CLIENT_INFO(...)
	#define GBC_CLIENT_WARN(...)
	#define GBC_CLIENT_ERROR(...)
	#define GBC_CLIENT_FATAL(...)
#endif
