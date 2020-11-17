#pragma once

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		enum : MouseCode
		{
			// From glfw3.h
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}

}

#define OGE_MOUSE_BUTTON_0      ::Hazel::Mouse::Button0
#define OGE_MOUSE_BUTTON_1      ::Hazel::Mouse::Button1
#define OGE_MOUSE_BUTTON_2      ::Hazel::Mouse::Button2
#define OGE_MOUSE_BUTTON_3      ::Hazel::Mouse::Button3
#define OGE_MOUSE_BUTTON_4      ::Hazel::Mouse::Button4
#define OGE_MOUSE_BUTTON_5      ::Hazel::Mouse::Button5
#define OGE_MOUSE_BUTTON_6      ::Hazel::Mouse::Button6
#define OGE_MOUSE_BUTTON_7      ::Hazel::Mouse::Button7
#define OGE_MOUSE_BUTTON_LAST   ::Hazel::Mouse::ButtonLast
#define OGE_MOUSE_BUTTON_LEFT   ::Hazel::Mouse::ButtonLeft
#define OGE_MOUSE_BUTTON_RIGHT  ::Hazel::Mouse::ButtonRight
#define OGE_MOUSE_BUTTON_MIDDLE ::Hazel::Mouse::ButtonMiddle