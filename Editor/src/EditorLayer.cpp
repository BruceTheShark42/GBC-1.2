#include "EditorLayer.h"

#ifdef GBC_ENABLE_IMGUI
	#include <ImGui/imgui.h>
	#include <ImGuizmo.h>

	// Panels
	#include "Panels/SceneHierarchyPanel.h"
	#include "Panels/StatisticsPanel.h"
	#include "Panels/PropertiesPanel.h"
	#include "Panels/ScenePanel.h"
#endif

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GBC/Scene/SceneSerializer.h"
#include "GBC/Utils/PlatformUtils.h"

namespace gbc
{
	EditorLayer::EditorLayer()
	{

	}

	void EditorLayer::onAttach()
	{
		auto& window = Application::get().getWindow();

#ifdef GBC_ENABLE_IMGUI
		framebuffer = Framebuffer::create({ window.getWidth(), window.getHeight() });
#endif

		scene = createRef<Scene>();
		scene->onViewportResize(window.getWidth(), window.getHeight());

#if 0
		auto squareEntity = scene->createEntity("Square 1");
		squareEntity.add<SpriteRendererComponent>(glm::vec4(0.870588f, 0.270588f, 0.270588f, 1.0f));

		auto squareEntity2 = scene->createEntity("Square 2");
		squareEntity2.add<SpriteRendererComponent>(glm::vec4(0.270588f, 0.870588f, 0.270588f, 1.0f));

		auto primaryCamera = scene->createEntity("Camera");
		primaryCamera.add<CameraComponent>();

		class CameraController2D : public ScriptableEntity
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
				auto& translation = GetComponent<TransformComponent>().translation;

				if (Input::isKeyPressed(KeyCode::A)) translation.x -= speed;
				if (Input::isKeyPressed(KeyCode::D)) translation.x += speed;
				if (Input::isKeyPressed(KeyCode::W)) translation.y += speed;
				if (Input::isKeyPressed(KeyCode::S)) translation.y -= speed;
			}
		};
		//primaryCamera.add<NativeScriptComponent>().bind<CameraController2D>();

		class CameraController3D : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				transform = &GetComponent<TransformComponent>();

				// Move the camera back so it can see the squares
				transform->translation.z += 3.0f;
			}

			void OnUpdate(TimeStep ts)
			{
				const float movementSpeed = 2.0f * ts;

				const glm::vec3 forward = movementSpeed * glm::vec3(cosf(transform->rotation.y), 0.0f, sinf(transform->rotation.y));
				const glm::vec3 left = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));

				if (Input::isKeyPressed(KeyCode::W)) { transform->translation.z -= forward.x; transform->translation.x -= forward.z; }
				if (Input::isKeyPressed(KeyCode::S)) { transform->translation.z += forward.x; transform->translation.x += forward.z; }
				if (Input::isKeyPressed(KeyCode::A)) { transform->translation.x -= left.z; transform->translation.z -= left.x; }
				if (Input::isKeyPressed(KeyCode::D)) { transform->translation.x += left.z; transform->translation.z += left.x; }
				if (Input::isKeyPressed(KeyCode::LeftShift)) transform->translation.y -= movementSpeed;
				if (Input::isKeyPressed(KeyCode::Space)) transform->translation.y += movementSpeed;

				// TODO: The reason this is being used is because ImGui still processes
				// mouse events when the the mouse state for glfw is GLFW_HIDDEN
				if (Input::isMouseButtonPressed(MouseCode::MBLeft))
				{
					const float rotationSpeed = 0.2f * ts;
					
					transform->rotation.y -= mouseDX * rotationSpeed;
					transform->rotation.x = std::min(std::max(transform->rotation.x - mouseDY * rotationSpeed, minPitch), maxPitch);
					mouseDX = 0.0f;
					mouseDY = 0.0f;

					// Rotation TODO: use mouse
					//if (Input::isKeyPressed(KeyCode::Left)) transform->rotation.y = transform->rotation.y + rotationSpeed;
					//if (Input::isKeyPressed(KeyCode::Right)) transform->rotation.y = transform->rotation.y - rotationSpeed;
					//if (Input::isKeyPressed(KeyCode::Down)) transform->rotation.x = std::max(transform->rotation.x - rotationSpeed, minPitch);
					//if (Input::isKeyPressed(KeyCode::Up)) transform->rotation.x = std::min(transform->rotation.x + rotationSpeed, maxPitch);
				}
			}

			void OnEvent(Event& event)
			{
				//if (event.getType() == EventType::KeyPress)
				//{
				//	KeyPressEvent& kpe = (KeyPressEvent&)event;

				//	if (!kpe.hasRepeated() && kpe.getKeyCode() == KeyCode::Escape)
				//	{
				//		// Capture the mouse for rotation
				//		auto& window = Application::get().getWindow();
				//		window.toggleCaptureMouse();
				//		mouseCaptured = window.getCaptureMouse();
				//	}
				//}
				//else 
				if (event.getType() == EventType::MouseMove)
				{
					MouseMoveEvent& mme = (MouseMoveEvent&)event;

					float mouseX = mme.getX();
					float mouseY = mme.getY();
					mouseDX = mouseX - lastMouseX;
					mouseDY = mouseY - lastMouseY;
					lastMouseX = mouseX;
					lastMouseY = mouseY;
				}
			}
		private:
			// Has to be a pointer because c++ doesn't like uninitialized references...
			TransformComponent* transform = nullptr;

			bool mouseCaptured = false;

			// TODO: this shouldn't have to exist because Input should handle it
			float lastMouseX = 0.0f;
			float lastMouseY = 0.0f;
			float mouseDX = 0.0f;
			float mouseDY = 0.0f;

			const float maxPitch = glm::radians(90.0f);
			const float minPitch = -maxPitch;
		};
		primaryCamera.add<NativeScriptComponent>().bind<CameraController3D>();
#endif

		SceneSerializer seralizer(scene);
		sceneFilePath = "assets/scenes/scene_backup.gscn";
		seralizer.deserialize(sceneFilePath);

#ifdef GBC_ENABLE_IMGUI
		StatisticsPanel* statisticsPanel = new StatisticsPanel();
		sceneHierarchyPanel = new SceneHierarchyPanel(scene);
		PropertiesPanel* propertiesPanel = new PropertiesPanel(scene, sceneHierarchyPanel);

		ScenePanel* scenePanel = new ScenePanel(sceneHierarchyPanel);
		scenePanel->setSceneFocused(&sceneFocused);
		scenePanel->setSceneHovered(&sceneHovered);
		scenePanel->setViewportSize(&viewportSize);
		scenePanel->setGizmoType(&gizmoType);
		scenePanel->setFramebuffer(framebuffer);

		panels["Statistics Panel"] = statisticsPanel;
		panels["Scene Hierarchy Panel"] = sceneHierarchyPanel;
		panels["Properties Panel"] = propertiesPanel;
		panels["Scene Panel"] = scenePanel;
#endif
	}

	void EditorLayer::onDetach()
	{
#ifdef GBC_ENABLE_IMGUI
		for (auto& [name, panel] : panels)
			delete panel;
#endif
	}

	void EditorLayer::onUpdate(TimeStep ts)
	{
#ifdef GBC_ENABLE_IMGUI
		if (const FramebufferSpecs& specs = framebuffer->getSpecs();
			(specs.width != viewportSize.x || specs.height != viewportSize.y) &&
			viewportSize.x > 0.0f && viewportSize.y > 0.0f)
		{
			framebuffer->resize((int)viewportSize.x, (int)viewportSize.y);
			scene->onViewportResize((int)viewportSize.x, (int)viewportSize.y);
		}
#else
		// Handle this in onEvent
#endif

		// Render
#ifdef GBC_ENABLE_STATS
		Renderer2D::resetStatistics();
#endif
#ifdef GBC_ENABLE_IMGUI
		framebuffer->bind();
#endif

		RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::clear();

		// Update Scene
		// TODO: this is bad dumb code
		// this is why rendering and updating should be separate,
		// so you can disable one and not the other by simply not calling the function
#ifdef GBC_ENABLE_IMGUI
		scene->onUpdate(sceneFocused ? ts : 0.0f);
		framebuffer->unbind();
#else
		scene->onUpdate(ts);
#endif
	}

	void EditorLayer::onEvent(Event& event)
	{
		scene->onEvent(event);

#ifndef GBC_ENABLE_IMGUI
		if (event.getType() == EventType::WindowResize)
		{
			WindowResizeEvent& wre = (WindowResizeEvent&)event;
			viewportSize.x = wre.getWidth();
			viewportSize.y = wre.getHeight();
			scene->onViewportResize(wre.getWidth(), wre.getHeight());
		}
#endif

		if (event.getType() == EventType::KeyPress)
		{
			KeyPressEvent& kpe = (KeyPressEvent&)event;
			const bool controlPressed = Input::isKeyPressed(KeyCode::LeftControl) || Input::isKeyPressed(KeyCode::RightControl);
			bool shiftPressed = Input::isKeyPressed(KeyCode::LeftShift) || Input::isKeyPressed(KeyCode::RightShift);

			if (!kpe.hasRepeated())
			{
				switch (kpe.getKeyCode())
				{
					case KeyCode::F11:
						Application::get().getWindow().toggleFullscreen();
						break;
					case KeyCode::N:
						if (controlPressed)
							newScene();
						break;
					case KeyCode::O:
						if (controlPressed)
							openScene();
						break;
					case KeyCode::S:
						if (controlPressed)
						{
							if (shiftPressed || sceneFilePath.empty())
								saveSceneAs();
							else
								saveScene(sceneFilePath);
						}
						break;

					// Gizmos
					case KeyCode::Q:
						gizmoType = -1;
						break;
					case KeyCode::W:
						gizmoType = ImGuizmo::TRANSLATE;
						break;
					case KeyCode::E:
						gizmoType = ImGuizmo::ROTATE;
						break;
					case KeyCode::R:
						gizmoType = ImGuizmo::SCALE;
						break;
				}
			}
		}
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
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
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
			ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(0.0f, 0.0f), dockspace_flags);

		if (ImGui::BeginMenuBar())
		{
			// Menus
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
					newScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					openScene();

				if (ImGui::MenuItem("Save", "Ctrl+S"))
					saveSceneAs();

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					saveSceneAs();

				// I want this to be the last one
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

			if (ImGui::BeginMenu("Panels"))
			{
				// Add panel to list of currently active panels so it can be rendered
				// If the panel already is in the list, however, just focus that panel
				// TODO: These menus should be abstracted just like the panels

				for (auto& [name, panel] : panels)
					if (ImGui::MenuItem(name.c_str())) panel->toggleEnabled();

				ImGui::EndMenu();
			}


			ImGui::EndMenuBar();
		}
		ImGui::End();

		for (auto& [name, panel] : panels)
			panel->onImGuiRender(ts);
	}
#endif

	void EditorLayer::newScene()
	{
		// This has a really big bug: if you have stuff in a scene
		// and create a new scene, add an entity witha a camera
		// (move it back a bit to see stuff), and add an entity with
		// a sprite renderer, old entities appear back in the scene.
		// Some of the old entities are still there, but others have
		// been overridden by the two entities you just added.
		scene = createRef<Scene>();
		scene->onViewportResize((int)viewportSize.x, (int)viewportSize.y);
		sceneHierarchyPanel->setContext(scene);
	}

	void EditorLayer::openScene()
	{
		std::string filePath = FileDialogs::openFile("GBC Scene (*.gscn)\0*.gscn\0");
		if (!filePath.empty())
		{
			scene = createRef<Scene>();
			scene->onViewportResize((int)viewportSize.x, (int)viewportSize.y);
			sceneHierarchyPanel->setContext(scene);

			SceneSerializer serializer(scene);
			serializer.deserialize(filePath);
			sceneFilePath = filePath;
		}
	}

	void EditorLayer::saveSceneAs()
	{
		std::string filePath = FileDialogs::saveFile("GBC Scene (*.gscn)\0*.gscn\0");
		if (!filePath.empty())
		{
			size_t index = filePath.find_last_of(".gscn");
			if (index != filePath.size() - 1)
				filePath += ".gscn";
			saveScene(filePath);
			sceneFilePath = filePath;
		}
	}

	void EditorLayer::saveScene(const std::string& filePath)
	{
		SceneSerializer serializer(scene);
		serializer.serialize(filePath);
	}
}
