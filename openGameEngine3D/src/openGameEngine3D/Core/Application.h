#pragma once

#include "openGameEngine3D/Core/Base.h"
#include "openGameEngine3D/Core/Window.h"
#include "openGameEngine3D/Core/LayerStack.h"
#include "openGameEngine3D/Events/Event.h"
#include "openGameEngine3D/Events/ApplicationEvent.h"

#include "openGameEngine3D/Core/Timestep.h"
#include "openGameEngine3D/ImGui/ImGuiLayer.h"

int main (int argc, char** argv);

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class Application
	{
	public:
		Application (const std::string& name = "openGameEngine3D App");
		virtual ~Application ();

		void OnEvent (Event& e);

		void PushLayer (Layer* layer);
		void PushOverlay (Layer* layer);

		Window& GetWindow ()	{	return *m_Window;	}

		void Close ();
		ImGuiLayer* GetImGuiLayer (){	return m_ImGuiLayer;	}

		static Application& Get ()	{	return *s_Instance;	}

	private:
		void Run ();

		bool OnWindowClose (WindowCloseEvent& e);
		bool OnWindowResize (WindowResizedEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main (int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication ();
}
