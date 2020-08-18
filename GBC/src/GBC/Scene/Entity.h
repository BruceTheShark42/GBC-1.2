#pragma once

#include <entt.hpp>
#include "Scene.h"

namespace gbc
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity&) = default;
	public:
		template<typename T, typename... Args>
		T& add(Args&& ... args)
		{
			GBC_ASSERT(!has<T>(), "Entity already has component!");
			return scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& remove()
		{
			GBC_ASSERT(has<T>(), "Entity does not component!");
			return scene->registry.remove<T>(handle);
		}

		template<typename T>
		T& get()
		{
			GBC_ASSERT(has<T>(), "Entity does not component!");
			return scene->registry.get<T>(handle);
		}

		template<typename T>
		bool has()
		{
			return scene->registry.has<T>(handle);
		}
	public:
		operator bool() const { return handle != entt::null; }
	private:
		entt::entity handle{ entt::null };
		Scene* scene = nullptr;
	};
}
