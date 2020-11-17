#pragma once

#include <glm/glm.hpp>
#include "openGameEngine3D/Core/KeyCodes.h"
#include "openGameEngine3D/Core/MouseCodes.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class Input
	{
	public:
		static bool IsKeyPressed (KeyCode key);
		static bool IsMouseButtonPressed (MouseCode button);
		static glm::vec2 GetMousePosition ();
		static float GetMouseX ();
		static float GetMouseY ();
	};
}
