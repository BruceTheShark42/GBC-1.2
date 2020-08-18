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
	public:
		Entity createEntity(const std::string& name = std::string());
	private:
		entt::registry registry;
		friend class Entity;
	};
}
