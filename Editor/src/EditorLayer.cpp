#include "EditorLayer.h"

#ifdef GBC_ENABLE_IMGUI
	#include <ImGui/imgui.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gbc
{
	EditorLayer::EditorLayer()
	{

	}

	void EditorLayer::onAttach()
	{
		auto& window = Application::get().getWindow();

#ifdef GBC_ENABLE_IMGUI
		fbo = FrameBuffer::create(FrameBufferSpecs(window.getWidth(), window.getHeight()));
#endif

		scene = createRef<Scene>();

		squareEntity = scene->createEntity("Square");
		squareEntity.add<SpriteRendererComponent>(glm::vec4(0.870588f, 0.270588f, 0.270588f, 1.0f));

		primaryCamera = scene->createEntity("Primary Camera");
		primaryCamera.add<CameraComponent>();

		class CameraController : public ScriptableEntity
		{
		public:
			//void OnCreate()
			//{
			//	
			//}

			//void OnDestroy()
			//{
			//	// TODO: doesn't get called
			//}

			void OnUpdate(TimeStep ts)
			{
				float speed = 5.0f * ts;
				auto& transform = GetComponent<TransformComponent>().transform;

				if (Input::isKeyPressed(KeyCode::A)) transform[3][0] -= speed;
				if (Input::isKeyPressed(KeyCode::D)) transform[3][0] += speed;
				if (Input::isKeyPressed(KeyCode::W)) transform[3][1] += speed;
				if (Input::isKeyPressed(KeyCode::S)) transform[3][1] -= speed;
			}
		};
		primaryCamera.add<NativeScriptComponent>().bind<CameraController>();

#ifdef GBC_ENABLE_IMGUI
		sceneHierarchyPanel.setContext(scene);
		propertiesPanel.setContext(scene);
		propertiesPanel.setSceneHierarchyPanel(&sceneHierarchyPanel);
		scenePanel.setContext(scene);
		scenePanel.setSceneFocused(&sceneFocused);
		scenePanel.setSceneHovered(&sceneHovered);
		scenePanel.setViewportSize(&viewportSize);
		scenePanel.setFBO(fbo);
#endif
		scene->onViewportResize((unsigned int)window.getWidth(), (unsigned int)window.getHeight());
	}

	void EditorLayer::onDetach()
	{
		
	}

	void EditorLayer::onUpdate(TimeStep ts)
	{
#ifdef GBC_ENABLE_IMGUI
		if (const FrameBufferSpecs& specs = fbo->getSpecs();
			(specs.width != viewportSize.x || specs.height != viewportSize.y) &&
			viewportSize.x > 0.0f && viewportSize.y > 0.0f)
		{
			fbo->resize((unsigned int)viewportSize.x, (unsigned int)viewportSize.y);
			scene->onViewportResize((unsigned int)viewportSize.x, (unsigned int)viewportSize.y);
		}
#else
		// Handle this in onEvent
#endif

		// Render
#ifdef GBC_ENABLE_STATS
		Renderer2D::resetStatistics();
#endif
#ifdef GBC_ENABLE_IMGUI
		fbo->bind();
#endif

		RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::clear();

		// Update Scene
		// TODO: this is bad dumb code
		// this is why rendering and updating should be separate,
		// so you can disable one and not the other
#ifdef GBC_ENABLE_IMGUI
		scene->onUpdate(sceneFocused ? ts : 0.0f);
#else
		scene->onUpdate(ts);
#endif

#ifdef GBC_ENABLE_IMGUI
		fbo->unbind();
#endif
	}

	void EditorLayer::onEvent(Event& event)
	{
#ifndef GBC_ENABLE_IMGUI
		if (event.getType() == EventType::WindowResize)
		{
			WindowResizeEvent& wre = (WindowResizeEvent&)event;
			scene->onViewportResize((unsigned int)wre.getWidth(), (unsigned int)wre.getHeight());
		}
#endif
	}

#ifdef GBC_ENABLE_IMGUI
	void EditorLayer::onImGuiRender(TimeStep ts)
	{
		static bool show = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &show, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
					Application::get().terminate();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				Window& window = Application::get().getWindow();
				if (ImGui::MenuItem(window.getFullscreen() ? "Windowed" : "Fullscreen"))
					window.toggleFullscreen();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		ImGui::End();

		sceneHierarchyPanel.onImGuiRender(ts);
		propertiesPanel.onImGuiRender(ts);
		statisticsPanel.onImGuiRender(ts);
		scenePanel.onImGuiRender(ts);
	}
#endif
}
