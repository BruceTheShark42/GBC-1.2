project "GBC"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gbcpch.h"
	pchsource "src/gbcpch.cpp"

	files {
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		"src",
		"vendor/spdlog/include",
		"%{includedir.GLFW}",
		"%{includedir.Glad}",
		"%{includedir.ImGui}",
		"%{includedir.glm}",
		"%{includedir.stb_image}",
		"%{includedir.entt}",
		"%{includedir.yaml_cpp}",
		"%{includedir.ImGuizmo}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
		flags {
			"NoPCH"
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