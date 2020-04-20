#ifdef GBC_PLATFORM_WINDOWS
	
#else
	#error GBC currently only supports Windows!
#endif

#ifdef GBC_DEBUG
	#define GBC_ENABLE_ASSERTS
#endif

#ifndef GBC_DIST
	#define GBC_ENABLE_IMGUI
#endif

#ifdef GBC_ENABLE_ASSERTS
	#define GBC_CORE_ASSERT(condition, ...) { if (!(condition)) { GBC_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
	#define GBC_ASSERT(condition, ...) { if (!(condition)) { GBC_ERROR(__VA_ARGS__); __debugbreak(); } }
#else
	#define GBC_CORE_ASSERT(condition, ...)
	#define GBC_ASSERT(condition, ...)
#endif

#define BIT(b) (1 << b)

#define GBC_BIND_FUNC(func) std::bind(&func, this, std::placeholders::_1)
