// For use by Clients

// Core
#include "GBC/Core/core.h"
#include "GBC/Core/Application.h"
#include "GBC/Core/Log.h"
#include "GBC/Core/TimeStep.h"
#include "GBC/Core/Input.h"
#include "GBC/Core/keyCodes.h"
#include "GBC/Core/mouseButtons.h"

// Events
#include "GBC/Events/KeyEvent.h"
#include "GBC/Events/MouseEvent.h"
#include "GBC/Events/WindowEvent.h"

// ImGui
#include "GBC/ImGui/ImGuiLayer.h"

// Layers
#include "GBC/Layers/Layer.h"

// Renderer
#include "GBC/Renderer/Renderer.h"
#include "GBC/Renderer/Renderer2D.h"
#include "GBC/Renderer/RenderCommand.h"
#include "GBC/Renderer/Buffer.h"
#include "GBC/Renderer/VertexArray.h"
#include "GBC/Renderer/Shader.h"
#include "GBC/Renderer/Texture.h"
#include "GBC/Renderer/SubTexture2D.h"
#include "GBC/Renderer/Framebuffer.h"

// Scene
#include "GBC/Scene/Scene.h"
#include "GBC/Scene/Entity.h"
#include "GBC/Scene/ScriptableEntity.h"
#include "GBC/Scene/Components.h"

// TODO: this should be the default 2D camera controller
// (an equivalent to the unity camera that I don't like the controlls for)
// Also I don't think it belongs in Renderer because it's basically a script??????
#include "GBC/Renderer/OrthographicCameraController.h"
