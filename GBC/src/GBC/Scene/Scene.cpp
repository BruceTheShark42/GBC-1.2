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
		auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::drawQuad(transform, sprite.color);
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
