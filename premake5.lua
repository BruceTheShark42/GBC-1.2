workspace "GBC-1.2"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includedir = {}
includedir["GLFW"] = "%{wks.location}/GBC/vendor/GLFW/include"
includedir["Glad"] = "%{wks.location}/GBC/vendor/Glad/include"
includedir["ImGui"] = "%{wks.location}/GBC/vendor/ImGui"
includedir["glm"] = "%{wks.location}/GBC/vendor/glm"
includedir["stb_image"] = "%{wks.location}/GBC/vendor/stb_image"
includedir["entt"] = "%{wks.location}/GBC/vendor/entt/include"
includedir["yaml_cpp"] = "%{wks.location}/GBC/vendor/yaml-cpp/include"
includedir["ImGuizmo"] = "%{wks.location}/GBC/vendor/ImGuizmo"

group "Dependencies"
	include "GBC/vendor/GLFW"
	include "GBC/vendor/Glad"
	include "GBC/vendor/ImGui"
	include "GBC/vendor/yaml-cpp"
group ""

include "GBC"
include "Sandbox"
include "Editor"
