#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>

/*
	David Milot
	License : MIT
*/

namespace openGameEngine3D
{
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera (float zoomLevel, float aspect, float zNear, float zFar, glm::vec3 position, glm::vec3 front, glm::vec3 up);

		void SetProjection (float zoomLevel, float aspect, float zNear, float zFar);

		const glm::vec3& GetPosition () const
		{
			return m_Position;
		}

		void SetPosition (const glm::vec3& position)
		{
			//std::cout << "PerspectiveCamera.h SetPosition = " << glm::to_string (position);
			m_Position = position; 
			RecalculateViewMatrix ();
		}

		float GetRotation () const
		{
			return m_Rotation;
		}
		void SetRotation (float rotation)
		{
			m_Rotation = rotation;
			RecalculateViewMatrix ();
		}

		const glm::mat4& GetProjectionMatrix () const
		{
			return m_ProjectionMatrix;
		}
		const glm::mat4& GetViewMatrix () const
		{
			return m_ViewMatrix;
		}
		const glm::mat4& GetViewProjectionMatrix () const
		{
			return m_ViewProjectionMatrix;
		}
	private:
		void RecalculateViewMatrix ();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}