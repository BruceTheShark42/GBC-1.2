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

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void ImGuiLayer::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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
		Application& application = Application::getInstance();
		io.DisplaySize = ImVec2((float)application.getWindow().getWidth(), (float)application.getWindow().getHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* window = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(window);
		}
	}

	void ImGuiLayer::onImGuiRender()
	{
		
	}

	void ImGuiLayer::onEvent(Event& e)
	{
		if (blockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.setHandled(e.isHandled() || (e.isInCategory(EventCategoryMouse)&  io.WantCaptureMouse)
									   || (e.isInCategory(EventCategoryKeyboard)&  io.WantCaptureKeyboard));
		}
	}
}
#endif
