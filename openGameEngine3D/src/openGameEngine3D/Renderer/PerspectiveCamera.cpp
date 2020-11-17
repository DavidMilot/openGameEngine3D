#include "ogepch.h"
#include "openGameEngine3D/Renderer/PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

/*
	David Milot
	License : MIT
*/

namespace openGameEngine3D
{
	PerspectiveCamera::PerspectiveCamera (float zoomLevel, float aspect, float zNear, float zFar, glm::vec3 position, glm::vec3 front, glm::vec3 up): 
		m_ProjectionMatrix (glm::perspective (glm::radians (zoomLevel), aspect, zNear, zFar)), 
		m_ViewMatrix (glm::lookAt (position, position + front, up)),
		m_Position (position)
	{
		OGE_PROFILE_FUNCTION ();
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetProjection (float zoomLevel, float aspect, float zNear, float zFar)
	{
		OGE_PROFILE_FUNCTION ();
		//m_ProjectionMatrix = glm::ortho (left, right, bottom, top, -1.0f, 1.0f);
		//m_ViewMatrix = glm::lookAt (Position, Position + Front, Up);
		m_ProjectionMatrix = glm::perspective (glm::radians (zoomLevel), aspect, zNear, zFar);
		//m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		//m_ProjectionMatrix
	}

	void PerspectiveCamera::RecalculateViewMatrix ()
	{
		OGE_PROFILE_FUNCTION ();
		glm::mat4 transform = glm::translate (glm::mat4 (1.0f), m_Position) * glm::rotate (glm::mat4 (1.0f), glm::radians (m_Rotation), glm::vec3 (0, 0, 1));
		m_ViewMatrix = glm::inverse (transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}