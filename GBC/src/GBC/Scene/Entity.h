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

		template<typename T, typename... Args>
		T& add(Args&& ... args)
		{
			GBC_CORE_ASSERT(!has<T>(), "Entity already has component!");
			T& component = scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
			scene->onComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		void remove()
		{
			GBC_CORE_ASSERT(has<T>(), "Entity does not component!");
			scene->registry.remove<T>(handle);
		}

		template<typename T>
		T& get()
		{
			GBC_CORE_ASSERT(has<T>(), "Entity does not component!");
			return scene->registry.get<T>(handle);
		}

		template<typename T>
		bool has()
		{
			return scene->registry.has<T>(handle);
		}

		inline operator bool() const { return handle != entt::null; }
		inline operator uint32_t() const { return static_cast<uint32_t>(handle); }
		inline operator entt::entity() const { return handle; }

		bool operator==(const Entity& entity) const { return handle == entity.handle && scene == entity.scene; }
		bool operator!=(const Entity& entity) const { return !(*this == entity); }
	private:
		entt::entity handle{ entt::null };
		Scene* scene = nullptr;
	};
}
