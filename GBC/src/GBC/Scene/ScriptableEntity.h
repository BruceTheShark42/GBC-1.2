#pragma once

#include "Entity.h"

namespace gbc
{
	class ScriptableEntity
	{
	public:
		template<typename T>
		T& GetComponent()
		{
			return entity.get<T>();
		}
	private:
		Entity entity;

		friend class Scene;
	};
}
