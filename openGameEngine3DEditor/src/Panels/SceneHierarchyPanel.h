#pragma once

#include "openGameEngine3D/Core/Base.h"
#include "openGameEngine3D/Core/Log.h"
#include "openGameEngine3D/Scene/Scene.h"
#include "openGameEngine3D/Scene/Entity.h"

/*
	Hazel Engine
	License : Apache 2.0
*/
namespace openGameEngine3D
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel () = default;
		SceneHierarchyPanel (const Ref<Scene>& scene);

		void SetContext (const Ref<Scene>& scene);

		void OnImGuiRender ();
	private:
		void DrawEntityNode (Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}