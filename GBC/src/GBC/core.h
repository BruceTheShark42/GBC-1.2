#ifdef GBC_PLATFORM_WINDOWS
	#ifdef GBC_BUILD_DLL
		#define	GBC_API __declspec(dllexport)
	#else
		#define GBC_API __declspec(dllimport)
	#endif
#else
	#error GBC currently only supports Windows!
#endif

#define BIT(b) (1 << b)
