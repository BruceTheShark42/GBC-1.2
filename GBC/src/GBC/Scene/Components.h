#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "SceneCamera.h"
#include "ScriptableEntity.h"

namespace gbc
{
	struct TagComponent
	{
		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: translation(translation) {}

		operator glm::mat4()
		{
			return glm::translate(glm::mat4(1.0f), translation) *
				   glm::toMat4(glm::quat(rotation)) *
				   glm::scale(glm::mat4(1.0f), scale);
			//return glm::scale(
			//	glm::rotate(
			//		glm::rotate(
			//			glm::rotate(
			//				glm::translate(glm::mat4(1.0f), translation),
			//				rotation.y, { 0.0f, 1.0f, 0.0f }),
			//			rotation.x, { 1.0f, 0.0f, 0.0f }),
			//		rotation.z, { 0.0f, 0.0f, 1.0f }),
			//	scale);
		}
	};

	struct CameraComponent
	{
		SceneCamera camera;
		bool primary = true; // TODO: move to scene
		bool fixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct SpriteRendererComponent
	{
		glm::vec4 color = glm::vec4(1.0f);

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: color(color) {}
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* instance = nullptr;

		ScriptableEntity* (*instantiateScript)();
		void (*destroyScript)(NativeScriptComponent*);

		template<typename T>
		void bind()
		{
			instantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			destroyScript = [](NativeScriptComponent* nsc) { delete nsc->instance; nsc->instance = nullptr; };
		}
	};
}
