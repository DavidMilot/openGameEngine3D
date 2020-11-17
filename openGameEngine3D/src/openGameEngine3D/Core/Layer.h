#pragma once

#include "openGameEngine3D/Core/Base.h"
#include "openGameEngine3D/Core/Timestep.h"
#include "openGameEngine3D/Events/Event.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class Layer
	{
	public:
		Layer (const std::string& name = "Layer");

		virtual ~Layer ();

		virtual void OnAttach (){}
		virtual void OnDetach (){}
		virtual void OnUpdate (){}
		virtual void OnImGuiRender (){}
		virtual void OnUpdate (Timestep ts)	{	}
		virtual void OnEvent  (Event& event){}

		const std::string& GetName () const
		{
			return m_DebugName;
		}

	protected:
		std::string m_DebugName;
	};
}