#pragma once

#include "Entity.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity ()	{	}

		template<typename T>
		T& GetComponent ()
		{
			return m_Entity.GetComponent<T> ();
		}
	protected:
		virtual void OnCreate ()	{	}
		virtual void OnDestroy ()	{	}
		virtual void OnUpdate (Timestep ts)	{	}
	private:
		Entity m_Entity;
		friend class Scene;
	};

}