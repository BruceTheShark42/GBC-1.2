#pragma once

#include <entt.hpp>
#include "GBC/Core/TimeStep.h"

namespace gbc
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();
	public:
		void onUpdate(TimeStep ts);
		void onViewportResize(unsigned int width, unsigned int height);
	public:
		Entity createEntity(const std::string& name = std::string());
	private:
		entt::registry registry;
		unsigned int viewportWidth = 0, viewportHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}
