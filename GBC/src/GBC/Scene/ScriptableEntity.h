#pragma once

#include "Entity.h"

namespace gbc
{
	class ScriptableEntity
	{
	public:
		ScriptableEntity() = default;
		virtual ~ScriptableEntity() = default;
	
		template<typename T>
		T& GetComponent()
		{
			return entity.get<T>();
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(TimeStep ts) {}
	private:
		Entity entity;

		friend class Scene;
	};
}
