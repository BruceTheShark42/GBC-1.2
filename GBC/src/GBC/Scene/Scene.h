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
		void onViewportResize(int width, int height);
	public:
		Entity createEntity(const std::string& name = std::string());
	private:
		entt::registry registry;
		int viewportWidth = 0;
		int viewportHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}
