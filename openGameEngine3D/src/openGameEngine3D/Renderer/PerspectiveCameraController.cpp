#include "ogepch.h"
#include "openGameEngine3D/Renderer/PerspectiveCameraController.h"

#include "openGameEngine3D/Core/Input.h"
#include "openGameEngine3D/Core/KeyCodes.h"

/*
	David Milot
	License : MIT
*/

namespace openGameEngine3D
{
	PerspectiveCameraController::PerspectiveCameraController (float aspectRatio, bool rotation, float zoomLevel, glm::vec3 position, glm::vec3 front, glm::vec3 up ):
		m_AspectRatio (aspectRatio), 
		m_Camera (zoomLevel, aspectRatio, 0.1f, 100.0f, position, front, up),
		m_Rotation (rotation)	
	{	}

	void PerspectiveCameraController::OnUpdate (Timestep ts)
	{
		OGE_PROFILE_FUNCTION ();

		/*if (Input::IsKeyPressed (Key::A))
		{
			m_CameraPosition.x -= cos (glm::radians (m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin (glm::radians (m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed (Key::D))
		{
			m_CameraPosition.x += cos (glm::radians (m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin (glm::radians (m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed (Key::W))
		{
			m_CameraPosition.x += -sin (glm::radians (m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos (glm::radians (m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed (Key::S))
		{
			m_CameraPosition.x -= -sin (glm::radians (m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos (glm::radians (m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}*/

		if (Input::IsKeyPressed (Key::A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed (Key::D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed (Key::W))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed (Key::S))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed (Key::Q))
		{
			m_CameraPosition.z += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed (Key::E))
		{
			m_CameraPosition.z -= m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{/*
			if (Input::IsKeyPressed (Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed (Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;*/

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation (m_CameraRotation);
		}

		m_Camera.SetPosition (m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
		//std::cout << "PerspectiveCameraController::OnUpdate ";
	}

	void PerspectiveCameraController::OnEvent (Event& e)
	{
		OGE_PROFILE_FUNCTION ();
		EventDispatcher dispatcher (e);
		dispatcher.Dispatch<MouseScrolledEvent> (OGE_BIND_EVENT_FN (PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizedEvent> (OGE_BIND_EVENT_FN (PerspectiveCameraController::OnWindowResized));
	}

	void PerspectiveCameraController::OnResize (float width, float height)
	{
		m_AspectRatio = width / height;
		//m_Camera.SetProjection (-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		m_Camera.SetProjection (m_ZoomLevel, m_AspectRatio, 0.1f, 100.0f);
	}

	bool PerspectiveCameraController::OnMouseScrolled (MouseScrolledEvent& e)
	{
		OGE_PROFILE_FUNCTION ();
		m_ZoomLevel -= e.GetYOffset () * 0.25f;
		m_ZoomLevel = std::max (m_ZoomLevel, 0.25f);
		//m_Camera.SetProjection (-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		m_Camera.SetProjection (glm::radians (m_ZoomLevel), m_AspectRatio, 0.1f, 100.0f);
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized (WindowResizedEvent& e)
	{
		OGE_PROFILE_FUNCTION ();
		OnResize ((float)e.GetWidth (), (float)e.GetHeight ());
		return false;
	}
}