#include "ogepch.h"
#include "Entity.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Entity::Entity (entt::entity handle, Scene* scene)
		: m_EntityHandle (handle), m_Scene (scene)	{ }
}