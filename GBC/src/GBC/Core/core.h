#pragma once

#include <memory>

#ifndef GBC_PLATFORM_WINDOWS
	#error GBC currently only supports Windows!
#endif

#ifdef GBC_DEBUG
	#define GBC_ENABLE_ASSERTS
	#define GBC_ENABLE_LOGGING
	#define GBC_ENABLE_IMGUI
	#define GBC_ENABLE_STATS
#endif

#ifdef GBC_RELEASE
	#define GBC_ENABLE_IMGUI
	#define GBC_ENABLE_STATS
#endif

#ifdef GBC_DIST
	
#endif

#ifdef GBC_ENABLE_ASSERTS
	#define GBC_CORE_ASSERT(condition, ...) if (!(condition)) { GBC_CORE_ERROR(__VA_ARGS__); __debugbreak(); }
	#define GBC_ASSERT(condition, ...) if (!(condition)) { GBC_ERROR(__VA_ARGS__); __debugbreak(); }
#else
	#define GBC_CORE_ASSERT(condition, ...)
	#define GBC_ASSERT(condition, ...)
#endif

#define BIT(b) (1 << b)

#define GBC_BIND_FUNC(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }

namespace gbc
{
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Ref<T> createRef(Args &&...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Scope<T> createScope(Args &&...args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
