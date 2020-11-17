#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>
#include <vector>
#include <iostream>

/*
	David Milot
	License : MIT
*/

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 20.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

namespace openGameEngine3D
{
	class Camera3D
	{
	public:
		// camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up = glm::vec3 (0.0f, 1.0f, 0.0f);
		glm::vec3 Right = glm::vec3 (0.0f, 0.0f, 0.0f);
		glm::vec3 WorldUp;

		// euler Angles
		float Yaw = YAW;
		float Pitch = PITCH;
		// camera options
		float MovementSpeed = SPEED;
		float MouseSensitivity = SENSITIVITY;
		float Zoom = ZOOM;

		Camera3D () = default;

		Camera3D (const glm::mat4& projection, glm::vec3 pos, glm::vec3 front, glm::vec3 up) :
			m_Projection (projection),
			Position (pos),
			Front (front),
			WorldUp (up)
		{
		//	/*Position = glm::vec3 (0.0f, 0.0f, 0.0f);
		//	Front = glm::vec3 (0.0f, 0.0f, -1.0f);
		//	Up = glm::vec3 (0.0f, 1.0f, 0.0f);
		//	Right = glm::vec3 (0.0f, 0.0f, 0.0f);
		//	WorldUp = glm::vec3 (0.0f, 0.0f, 0.0f);*/
		//	//std::cout << "Camera3D constructor called with a m_Project set to = " << glm::to_string (m_Projection) << std::endl;
		// std::cout << "Camera 3D constructor = projection, pos, front, up";
		}

		Camera3D (const glm::mat4& projection) : m_Projection (projection)	
		{	
		//	std::cout << "Camera 3D constructor = projection = " << glm::to_string (projection) << std::endl;
		}

		const glm::mat4& GetProjection () const
		{	
			return m_Projection;	
		}

		glm::mat4& GetViewMatrix ()
		{
			return glm::lookAt (Position, Position + Front, Up);
		}

		glm::vec3 GetPosition ()
		{
			return Position;
		}

		float GetZoom ()
		{
			return Zoom;
		}

		// returns the view matrix calculated using Euler Angles and the LookAt Matrix
		// returns the view matrix calculated using Euler Angles and the LookAt Matrix

		//Camera3D (const glm::mat4& projection) : m_Projection (projection)	{	}

		// constructor with vectors

		/*
		Camera3D (glm::vec3 position = glm::vec3 (0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3 (0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front (glm::vec3 (0.0f, 0.0f, -1.0f)), MovementSpeed (SPEED), MouseSensitivity (SENSITIVITY), Zoom (ZOOM)
		{
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;
			//updateCameraVectors ();
		}*/

	private:
		// calculates the front vector from the Camera's (updated) Euler Angles
		void updateCameraVectors ()		{		}
	protected:
		glm::mat4 m_Projection = glm::mat4 (1.0f);
	};
}