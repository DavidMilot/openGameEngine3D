#include "ogepch.h"
#include "openGameEngine3D/Core/Application.h"
#include "openGameEngine3D/Core/Log.h"
#include "openGameEngine3D/Core/Input.h"
#include "openGameEngine3D/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Application* Application::s_Instance = nullptr;

	Application::Application (const std::string& name)
	{
		OGE_PROFILE_FUNCTION ();

		//OGE_CORE_ASSERT (!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create (WindowProps (name));
		m_Window->SetEventCallback (OGE_BIND_EVENT_FN (Application::OnEvent));

		Renderer::Init ();

		m_ImGuiLayer = new ImGuiLayer ();
		PushOverlay (m_ImGuiLayer);
	}

	Application::~Application ()
	{
		OGE_PROFILE_FUNCTION ();

		Renderer::Shutdown ();
	}

	void Application::PushLayer (Layer* layer)
	{
		OGE_PROFILE_FUNCTION ();

		m_LayerStack.PushLayer (layer);
		layer->OnAttach ();
	}

	void Application::PushOverlay (Layer* layer)
	{
		OGE_PROFILE_FUNCTION ();

		m_LayerStack.PushOverlay (layer);
		layer->OnAttach ();
	}

	void Application::Close ()
	{
		m_Running = false;
	}

	void Application::OnEvent (Event& e)
	{
		OGE_PROFILE_FUNCTION ();

		EventDispatcher dispatcher (e);
		dispatcher.Dispatch<WindowCloseEvent> (OGE_BIND_EVENT_FN (Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent> (OGE_BIND_EVENT_FN (Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin (); it != m_LayerStack.rend (); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent (e);
		}
	}

	void Application::Run ()
	{
		OGE_PROFILE_FUNCTION ();

		while (m_Running)
		{
			OGE_PROFILE_SCOPE ("RunLoop");

			float time = (float)glfwGetTime ();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					OGE_PROFILE_SCOPE ("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate (timestep);
				}

				m_ImGuiLayer->Begin ();
				{
					OGE_PROFILE_SCOPE ("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender ();
				}
				m_ImGuiLayer->End ();
			}

			m_Window->OnUpdate ();
		}
	}

	bool Application::OnWindowClose (WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize (WindowResizedEvent& e)
	{
		OGE_PROFILE_FUNCTION ();

		if (e.GetWidth () == 0 || e.GetHeight () == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize (e.GetWidth (), e.GetHeight ());

		return false;
	}

}