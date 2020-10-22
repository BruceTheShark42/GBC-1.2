#include "gbcpch.h"

#ifdef GBC_ENABLE_IMGUI
#include "GBC/Core/Application.h"
#include "ImGuiLayer.h"
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace gbc
{
	void ImGuiLayer::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Set the default font
		io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans/OpenSans-Regular.ttf", 18.0f);

		setDarkThemeColors();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			style.WindowRounding = 0.0f;

		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	void ImGuiLayer::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::setDarkThemeColors()
	{
		ImGui::StyleColorsDark();

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = { 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = { 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = { 0.15f, 0.155f, 0.16f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = { 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = { 0.15f, 0.155f, 0.16f, 1.0f };

		// Frame Background
		colors[ImGuiCol_FrameBg] = { 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = { 0.15f, 0.155f, 0.16f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = { 0.15f, 0.155f, 0.16f, 1.0f };
		colors[ImGuiCol_TabHovered] = { 0.38f, 0.385f, 0.39f, 1.0f };
		colors[ImGuiCol_TabActive] = { 0.28f, 0.285f, 0.29f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = { 0.15f, 0.155f, 0.16f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = { 0.2f, 0.205f, 0.21f, 1.0f };

		// Title Background
		colors[ImGuiCol_TitleBg] = { 0.15f, 0.155f, 0.16f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = { 0.15f, 0.155f, 0.16f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = { 0.15f, 0.155f, 0.16f, 1.0f };
	}

	void ImGuiLayer::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Window& window = Application::get().getWindow();
		io.DisplaySize = ImVec2((float)window.getWidth(), (float)window.getHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* windowHandle = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(windowHandle);
		}
	}

	void ImGuiLayer::onEvent(Event& e)
	{
		if (blockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.handled = e.handled || (e.isInCategory(EventCategory_Mouse) && io.WantCaptureMouse)
								  || (e.isInCategory(EventCategory_Keyboard) && io.WantCaptureKeyboard);
		}
	}
}
#endif
