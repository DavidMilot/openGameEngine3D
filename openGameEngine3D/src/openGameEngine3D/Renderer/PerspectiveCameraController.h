#pragma once

#include "openGameEngine3D/Renderer/PerspectiveCamera.h"
#include "openGameEngine3D/Core/Timestep.h"

#include "openGameEngine3D/Events/ApplicationEvent.h"
#include "openGameEngine3D/Events/MouseEvent.h"

/*
	David Milot
	License : MIT
*/

namespace openGameEngine3D
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController (float aspectRatio, bool rotation, float zoomLevel, glm::vec3 position, glm::vec3 front, glm::vec3 up);

		void OnUpdate (Timestep ts);
		void OnEvent (Event& e);
		void OnResize (float width, float height);

		PerspectiveCamera& GetCamera ()
		{
			return m_Camera;
		}
		const PerspectiveCamera& GetCamera () const
		{
			return m_Camera;
		}

		//float GetZoomLevel () const
		//{
		//	return m_ZoomLevel;
		//}
		//void SetZoomLevel (float level)
		//{
		//	m_ZoomLevel = level;
		//}
	private:
		bool OnMouseScrolled (MouseScrolledEvent& e);
		bool OnWindowResized (WindowResizedEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		PerspectiveCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f,0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
}