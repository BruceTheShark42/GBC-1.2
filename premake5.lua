workspace "GBC 1.2"
	architecture "x64"
	startproject "Sandbox"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GBC"
	location "GBC"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gbcpch.h"
	pchsource "GBC/src/gbcpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"GBC_PLATFORM_WINDOWS",
			"GBC_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "GBC_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "GBC_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "GBC_DIST"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"GBC/vendor/spdlog/include",
		"GBC/src"
	}

	links {
		"GBC"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"GBC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GBC_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "GBC_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "GBC_DIST"
		optimize "on"