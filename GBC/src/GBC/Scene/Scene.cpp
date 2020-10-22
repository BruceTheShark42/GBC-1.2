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
		// Update Scripts
		if (ts > 0.0f)
		{
			registry.view<NativeScriptComponent>().each([=](entt::entity entity, NativeScriptComponent& nsc)
				{
					// TODO: move to Scene::onScenePlay
					if (!nsc.instance)
					{
						nsc.instance = nsc.instantiateScript();
						nsc.instance->entity = Entity{ entity, this };
						nsc.instance->OnCreate();
					}

					nsc.instance->OnUpdate(ts);
					// TODO: add "nsc.instance->OnDestroy();" to Scene::onSceneStop
				});
		}

		// Get the primary camera
		Camera* primaryCamera = nullptr;
		glm::mat4 primaryTransform;
		{
			auto view = registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.primary)
				{
					primaryCamera = &camera.camera;
					primaryTransform = transform;
					break;
				}
			}
		}

		if (primaryCamera)
		{
			// Render 2D
			Renderer2D::beginScene(*primaryCamera, primaryTransform);

			auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::drawQuad(transform, sprite.color);
			}

			Renderer2D::endScene();
		}
	}

	void Scene::onViewportResize(int width, int height)
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

	void Scene::destroyEntity(Entity entity)
	{
		registry.destroy(entity);
	}

	template<typename T>
	void Scene::onComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::onComponentAdded<TagComponent>(Entity entity, TagComponent& component) {}

	template<>
	void Scene::onComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) {}

	template<>
	void Scene::onComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.camera.setViewportSize(viewportWidth, viewportHeight);
	}

	template<>
	void Scene::onComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component) {}

	template<>
	void Scene::onComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component) {}
}
