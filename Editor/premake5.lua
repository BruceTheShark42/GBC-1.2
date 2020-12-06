project "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/GBC/vendor/spdlog/include",
		"%{wks.location}/GBC/src",
		"%{wks.location}/GBC/vendor",
		"%{includedir.glm}",
		"%{includedir.entt}",
		"%{includedir.ImGuizmo}"
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
