#pragma once

#include "openGameEngine3D/Core/Layer.h"
#include "openGameEngine3D/Events/ApplicationEvent.h"
#include "openGameEngine3D/Events/KeyEvent.h"
#include "openGameEngine3D/Events/MouseEvent.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer ();
		~ImGuiLayer () = default;

		virtual void OnAttach ();
		virtual void OnDetach ();
		virtual void OnEvent (Event& e) override;

		void Begin ();
		void End ();
		void BlockEvents (bool block)	{	m_BlockEvents = block;	}

	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};

}