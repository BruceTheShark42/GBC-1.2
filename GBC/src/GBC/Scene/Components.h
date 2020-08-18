#pragma once

#include <glm/glm.hpp>
#include "SceneCamera.h"
#include "ScriptableEntity.h"

namespace gbc
{
	struct TransformComponent
	{
		glm::mat4 transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: transform(transform) {}

		operator glm::mat4& () { return transform; }
		operator const glm::mat4& () const { return transform; }
	};

	struct TagComponent
	{
		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: tag(tag) {}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 color = glm::vec4(1.0f);

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera camera;
		bool primary = true; // TODO: move to scene
		bool fixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* instance = nullptr;

		std::function<void()> instantiateFunc;
		std::function<void()> destroyInstanceFunc;

		std::function<void(ScriptableEntity*)> onCreateFunc;
		std::function<void(ScriptableEntity*)> onDestroyFunc;
		std::function<void(ScriptableEntity*, TimeStep)> onUpdateFunc;

		template<typename T>
		void bind()
		{
			instantiateFunc = [&]() { instance = new T(); };
			destroyInstanceFunc = [&]() { delete (T*)instance; instance = nullptr; };

			onCreateFunc = [](ScriptableEntity* instance) { ((T*)instance)->OnCreate(); };
			onDestroyFunc = [](ScriptableEntity* instance) { ((T*)instance)->OnDestroy(); };
			onUpdateFunc = [](ScriptableEntity* instance, TimeStep ts) { ((T*)instance)->OnUpdate(ts); };
		}
	};
}
