#pragma once

#include "openGameEngine3D/Renderer/Camera3D.h"

/*
	David Milot
	License : MIT
*/

namespace openGameEngine3D
{
	class Scene3DCamera : public Camera3D
	{
	public:
		Scene3DCamera ();
		virtual ~Scene3DCamera () = default;

		void SetProjection (float zoomLevel, float aspect, float zNear, float zFar);
		// returns the view matrix calculated using Euler Angles and the LookAt Matrix
		
		glm::mat4 GetViewMatrix ();

		void SetViewportSize (uint32_t width, uint32_t height);

		//This is the same as Field of View
		void SetZoom (float zoom);

		//This is the same as Field of View
		float GetZoom ();

		void SetPosition (glm::vec3 pos);

		glm::vec3 Scene3DCamera::GetPosition ();

	private:
		void updateCameraVectors ();
	private:
		float m_ProjectionNear = 0.1f;
		float m_ProjectionFar = 1000.0f;
		float m_AspectRatio = 1.5f;
		float m_Zoom = 60.0f;
	};
}