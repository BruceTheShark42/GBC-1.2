#pragma once

#include <entt.hpp>
#include "GBC/Core/TimeStep.h"
#include "GBC/Events/Event.h"

namespace gbc
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void onUpdate(TimeStep ts);
		void onEvent(Event& event);
		void onViewportResize(int width, int height);

		Entity createEntity(const std::string& name = std::string());
		void destroyEntity(Entity entity);
	private:
		template<typename T>
		void onComponentAdded(Entity entity, T& component);

		entt::registry registry;
		int viewportWidth = 0;
		int viewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		// TODO: this is a baaaadaad idea
		friend class SceneHierarchyPanel;
	};
}
