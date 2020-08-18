#include "gbcpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "GBC/Renderer/Renderer2D.h"

namespace gbc
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::onUpdate(TimeStep ts)
	{
		// Get the primary camera
		Camera* primaryCamera = nullptr;
		glm::mat4* primaryTransform = nullptr;
		{
			auto view = registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.primary)
				{
					primaryCamera = &camera.camera;
					primaryTransform = &transform.transform;
					break;
				}
			}
		}

		if (primaryCamera)
		{
			// Render 2D
			Renderer2D::beginScene(*primaryCamera, *primaryTransform);

			auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::drawQuad(transform, sprite.color);
			}

			Renderer2D::endScene();
		}
	}

	void Scene::onViewportResize(unsigned int width, unsigned int height)
	{
		viewportWidth = width;
		viewportHeight = height;

		// Resize the non-fixedAspectRatio cameras
		auto view = registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity);
			if (!camera.fixedAspectRatio)
				camera.camera.setViewportSize(width, height);
		}
	}

	Entity Scene::createEntity(const std::string& name)
	{
		Entity entity(registry.create(), this);
		entity.add<TransformComponent>();
		
		auto& tag = entity.add<TagComponent>();
		tag.tag = name.empty() ? "Entity" : name;

		return entity;
	}
}
