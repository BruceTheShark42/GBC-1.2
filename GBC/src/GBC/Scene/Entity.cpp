#include "gbcpch.h"
#include "Entity.h"

namespace gbc
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: handle(handle), scene(scene) {}
}
