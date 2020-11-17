#pragma once

#include "entt.hpp"
#include "openGameEngine3D/Core/Timestep.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class Entity;

	class Scene
	{
	public:
		Scene ();
		~Scene ();

		entt::entity CreateEntity ();

		// TEMP
		entt::registry& Reg ()
		{
			return m_Registry;
		}
		Entity CreateEntity (const std::string& name = std::string ());

		void OnUpdate (Timestep ts);
		void OnViewportResize (uint32_t width, uint32_t height);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		friend class SceneHierarchyPanel;

		friend class Entity;
	};

}