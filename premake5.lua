workspace "GBC 1.2"
	architecture "x64"
	startproject "Sandbox"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includedir = {}
includedir["GLFW"] = "GBC/vendor/GLFW/include"
includedir["Glad"] = "GBC/vendor/Glad/include"
includedir["ImGui"] = "GBC/vendor/ImGui"
includedir["glm"] = "GBC/vendor/glm"
includedir["stb_image"] = "GBC/vendor/stb_image"

group "Dependencies"
	include "GBC/vendor/GLFW"
	include "GBC/vendor/Glad"
	include "GBC/vendor/ImGui"
group ""

project "GBC"
	location "GBC"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gbcpch.h"
	pchsource "GBC/src/gbcpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{includedir.GLFW}",
		"%{includedir.Glad}",
		"%{includedir.ImGui}",
		"%{includedir.glm}",
		"%{includedir.stb_image}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"GBC_PLATFORM_WINDOWS",
			"GBC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GBC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GBC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GBC_DIST"
		runtime "Release"
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
		"GBC/src",
		"GBC/vendor",
		"%{includedir.glm}"
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
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GBC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GBC_DIST"
		runtime "Release"
		optimize "on"
		
project "Editor"
	location "Editor"
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
		"GBC/src",
		"GBC/vendor",
		"%{includedir.glm}"
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
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GBC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GBC_DIST"
		runtime "Release"
		optimize "on"
