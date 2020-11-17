#include "ogepch.h"
#include "Scene3DCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>

/*
	David Milot
	License : MIT
*/

namespace openGameEngine3D
{
	Scene3DCamera::Scene3DCamera (	) 
	{
		updateCameraVectors ();
	}

	void Scene3DCamera::SetProjection (float zoomLevel, float aspect, float zNear, float zFar)
	{
		m_Zoom = zoomLevel;
		m_AspectRatio = aspect;
		m_ProjectionNear = zNear;
		m_ProjectionFar = zFar;
		m_Projection = glm::perspective (glm::radians (m_Zoom), m_AspectRatio, m_ProjectionNear, m_ProjectionFar);
	}

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 Scene3DCamera::GetViewMatrix ()
	{
		return glm::lookAt (Position, Position + Front, Up);
	}
	
	void Scene3DCamera::SetViewportSize (uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		updateCameraVectors ();
	}

	void Scene3DCamera::SetZoom (float FOV)
	{
		m_Zoom = FOV;
		updateCameraVectors ();
	}

	float Scene3DCamera::GetZoom ()
	{
		return m_Zoom;
	}

	void Scene3DCamera::SetPosition (glm::vec3 pos)
	{
		Position = pos;
		//std::cout << "Scene3DCamera::SetPosition = " << glm::to_string (Position) << std::endl;

		updateCameraVectors ();
	}

	glm::vec3 Scene3DCamera::GetPosition ()
	{
		return Position;
	}

	void Scene3DCamera::updateCameraVectors ()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos (glm::radians (Yaw)) * cos (glm::radians (Pitch));
		front.y = sin (glm::radians (Pitch));
		front.z = sin (glm::radians (Yaw)) * cos (glm::radians (Pitch));
		Front = glm::normalize (front);
		// also re-calculate the Right and Up vector
		Right = glm::normalize (glm::cross (Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize (glm::cross (Right, Front));

		m_Projection = glm::perspective (glm::radians (m_Zoom), m_AspectRatio, m_ProjectionNear, m_ProjectionFar);
		//std::cout << "Scene3DCamera Projection = " << glm::to_string (m_Projection) << std::endl;

		//std::cout << glm::to_string (m_Projection) << std::endl;

	}
}