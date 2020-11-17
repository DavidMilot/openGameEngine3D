#pragma once

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	using KeyCode = uint16_t;

	namespace Key
	{
		enum : KeyCode
		{
			// From glfw3.h
			Space = 32,
			Apostrophe = 39, /* ' */
			Comma = 44, /* , */
			Minus = 45, /* - */
			Period = 46, /* . */
			Slash = 47, /* / */

			D0 = 48, /* 0 */
			D1 = 49, /* 1 */
			D2 = 50, /* 2 */
			D3 = 51, /* 3 */
			D4 = 52, /* 4 */
			D5 = 53, /* 5 */
			D6 = 54, /* 6 */
			D7 = 55, /* 7 */
			D8 = 56, /* 8 */
			D9 = 57, /* 9 */

			Semicolon = 59, /* ; */
			Equal = 61, /* = */

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 91,  /* [ */
			Backslash = 92,  /* \ */
			RightBracket = 93,  /* ] */
			GraveAccent = 96,  /* ` */

			World1 = 161, /* non-US #1 */
			World2 = 162, /* non-US #2 */

			/* Function keys */
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,
			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,
			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,

			/* Keypad */
			KP0 = 320,
			KP1 = 321,
			KP2 = 322,
			KP3 = 323,
			KP4 = 324,
			KP5 = 325,
			KP6 = 326,
			KP7 = 327,
			KP8 = 328,
			KP9 = 329,
			KPDecimal = 330,
			KPDivide = 331,
			KPMultiply = 332,
			KPSubtract = 333,
			KPAdd = 334,
			KPEnter = 335,
			KPEqual = 336,

			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347,
			Menu = 348
		};
	}
}

// From glfw3.h
#define OGE_KEY_SPACE           ::openGameEngine3D::Key::Space
#define OGE_KEY_APOSTROPHE      ::openGameEngine3D::Key::Apostrophe    /* ' */
#define OGE_KEY_COMMA           ::openGameEngine3D::Key::Comma         /* , */
#define OGE_KEY_MINUS           ::openGameEngine3D::Key::Minus         /* - */
#define OGE_KEY_PERIOD          ::openGameEngine3D::Key::Period        /* . */
#define OGE_KEY_SLASH           ::openGameEngine3D::Key::Slash         /* / */
#define OGE_KEY_0               ::openGameEngine3D::Key::D0
#define OGE_KEY_1               ::openGameEngine3D::Key::D1
#define OGE_KEY_2               ::openGameEngine3D::Key::D2
#define OGE_KEY_3               ::openGameEngine3D::Key::D3
#define OGE_KEY_4               ::openGameEngine3D::Key::D4
#define OGE_KEY_5               ::openGameEngine3D::Key::D5
#define OGE_KEY_6               ::openGameEngine3D::Key::D6
#define OGE_KEY_7               ::openGameEngine3D::Key::D7
#define OGE_KEY_8               ::openGameEngine3D::Key::D8
#define OGE_KEY_9               ::openGameEngine3D::Key::D9
#define OGE_KEY_SEMICOLON       ::openGameEngine3D::Key::Semicolon     /* ; */
#define OGE_KEY_EQUAL           ::openGameEngine3D::Key::Equal         /* = */
#define OGE_KEY_A               ::openGameEngine3D::Key::A
#define OGE_KEY_B               ::openGameEngine3D::Key::B
#define OGE_KEY_C               ::openGameEngine3D::Key::C
#define OGE_KEY_D               ::openGameEngine3D::Key::D
#define OGE_KEY_E               ::openGameEngine3D::Key::E
#define OGE_KEY_F               ::openGameEngine3D::Key::F
#define OGE_KEY_G               ::openGameEngine3D::Key::G
#define OGE_KEY_H               ::openGameEngine3D::Key::H
#define OGE_KEY_I               ::openGameEngine3D::Key::I
#define OGE_KEY_J               ::openGameEngine3D::Key::J
#define OGE_KEY_K               ::openGameEngine3D::Key::K
#define OGE_KEY_L               ::openGameEngine3D::Key::L
#define OGE_KEY_M               ::openGameEngine3D::Key::M
#define OGE_KEY_N               ::openGameEngine3D::Key::N
#define OGE_KEY_O               ::openGameEngine3D::Key::O
#define OGE_KEY_P               ::openGameEngine3D::Key::P
#define OGE_KEY_Q               ::openGameEngine3D::Key::Q
#define OGE_KEY_R               ::openGameEngine3D::Key::R
#define OGE_KEY_S               ::openGameEngine3D::Key::S
#define OGE_KEY_T               ::openGameEngine3D::Key::T
#define OGE_KEY_U               ::openGameEngine3D::Key::U
#define OGE_KEY_V               ::openGameEngine3D::Key::V
#define OGE_KEY_W               ::openGameEngine3D::Key::W
#define OGE_KEY_X               ::openGameEngine3D::Key::X
#define OGE_KEY_Y               ::openGameEngine3D::Key::Y
#define OGE_KEY_Z               ::openGameEngine3D::Key::Z
#define OGE_KEY_LEFT_BRACKET    ::openGameEngine3D::Key::LeftBracket   /* [ */
#define OGE_KEY_BACKSLASH       ::openGameEngine3D::Key::Backslash     /* \ */
#define OGE_KEY_RIGHT_BRACKET   ::openGameEngine3D::Key::RightBracket  /* ] */
#define OGE_KEY_GRAVE_ACCENT    ::openGameEngine3D::Key::GraveAccent   /* ` */
#define OGE_KEY_WORLD_1         ::openGameEngine3D::Key::World1        /* non-US #1 */
#define OGE_KEY_WORLD_2         ::openGameEngine3D::Key::World2        /* non-US #2 */

/* Function keys */
#define OGE_KEY_ESCAPE          ::openGameEngine3D::Key::Escape
#define OGE_KEY_ENTER           ::openGameEngine3D::Key::Enter
#define OGE_KEY_TAB             ::openGameEngine3D::Key::Tab
#define OGE_KEY_BACKSPACE       ::openGameEngine3D::Key::Backspace
#define OGE_KEY_INSERT          ::openGameEngine3D::Key::Insert
#define OGE_KEY_DELETE          ::openGameEngine3D::Key::Delete
#define OGE_KEY_RIGHT           ::openGameEngine3D::Key::Right
#define OGE_KEY_LEFT            ::openGameEngine3D::Key::Left
#define OGE_KEY_DOWN            ::openGameEngine3D::Key::Down
#define OGE_KEY_UP              ::openGameEngine3D::Key::Up
#define OGE_KEY_PAGE_UP         ::openGameEngine3D::Key::PageUp
#define OGE_KEY_PAGE_DOWN       ::openGameEngine3D::Key::PageDown
#define OGE_KEY_HOME            ::openGameEngine3D::Key::Home
#define OGE_KEY_END             ::openGameEngine3D::Key::End
#define OGE_KEY_CAPS_LOCK       ::openGameEngine3D::Key::CapsLock
#define OGE_KEY_SCROLL_LOCK     ::openGameEngine3D::Key::ScrollLock
#define OGE_KEY_NUM_LOCK        ::openGameEngine3D::Key::NumLock
#define OGE_KEY_PRINT_SCREEN    ::openGameEngine3D::Key::PrintScreen
#define OGE_KEY_PAUSE           ::openGameEngine3D::Key::Pause
#define OGE_KEY_F1              ::openGameEngine3D::Key::F1
#define OGE_KEY_F2              ::openGameEngine3D::Key::F2
#define OGE_KEY_F3              ::openGameEngine3D::Key::F3
#define OGE_KEY_F4              ::openGameEngine3D::Key::F4
#define OGE_KEY_F5              ::openGameEngine3D::Key::F5
#define OGE_KEY_F6              ::openGameEngine3D::Key::F6
#define OGE_KEY_F7              ::openGameEngine3D::Key::F7
#define OGE_KEY_F8              ::openGameEngine3D::Key::F8
#define OGE_KEY_F9              ::openGameEngine3D::Key::F9
#define OGE_KEY_F10             ::openGameEngine3D::Key::F10
#define OGE_KEY_F11             ::openGameEngine3D::Key::F11
#define OGE_KEY_F12             ::openGameEngine3D::Key::F12
#define OGE_KEY_F13             ::openGameEngine3D::Key::F13
#define OGE_KEY_F14             ::openGameEngine3D::Key::F14
#define OGE_KEY_F15             ::openGameEngine3D::Key::F15
#define OGE_KEY_F16             ::openGameEngine3D::Key::F16
#define OGE_KEY_F17             ::openGameEngine3D::Key::F17
#define OGE_KEY_F18             ::openGameEngine3D::Key::F18
#define OGE_KEY_F19             ::openGameEngine3D::Key::F19
#define OGE_KEY_F20             ::openGameEngine3D::Key::F20
#define OGE_KEY_F21             ::openGameEngine3D::Key::F21
#define OGE_KEY_F22             ::openGameEngine3D::Key::F22
#define OGE_KEY_F23             ::openGameEngine3D::Key::F23
#define OGE_KEY_F24             ::openGameEngine3D::Key::F24
#define OGE_KEY_F25             ::openGameEngine3D::Key::F25

/* Keypad */
#define OGE_KEY_KP_0            ::openGameEngine3D::Key::KP0
#define OGE_KEY_KP_1            ::openGameEngine3D::Key::KP1
#define OGE_KEY_KP_2            ::openGameEngine3D::Key::KP2
#define OGE_KEY_KP_3            ::openGameEngine3D::Key::KP3
#define OGE_KEY_KP_4            ::openGameEngine3D::Key::KP4
#define OGE_KEY_KP_5            ::openGameEngine3D::Key::KP5
#define OGE_KEY_KP_6            ::openGameEngine3D::Key::KP6
#define OGE_KEY_KP_7            ::openGameEngine3D::Key::KP7
#define OGE_KEY_KP_8            ::openGameEngine3D::Key::KP8
#define OGE_KEY_KP_9            ::openGameEngine3D::Key::KP9
#define OGE_KEY_KP_DECIMAL      ::openGameEngine3D::Key::KPDecimal
#define OGE_KEY_KP_DIVIDE       ::openGameEngine3D::Key::KPDivide
#define OGE_KEY_KP_MULTIPLY     ::openGameEngine3D::Key::KPMultiply
#define OGE_KEY_KP_SUBTRACT     ::openGameEngine3D::Key::KPSubtract
#define OGE_KEY_KP_ADD          ::openGameEngine3D::Key::KPAdd
#define OGE_KEY_KP_ENTER        ::openGameEngine3D::Key::KPEnter
#define OGE_KEY_KP_EQUAL        ::openGameEngine3D::Key::KPEqual

#define OGE_KEY_LEFT_SHIFT      ::openGameEngine3D::Key::LeftShift
#define OGE_KEY_LEFT_CONTROL    ::openGameEngine3D::Key::LeftControl
#define OGE_KEY_LEFT_ALT        ::openGameEngine3D::Key::LeftAlt
#define OGE_KEY_LEFT_SUPER      ::openGameEngine3D::Key::LeftSuper
#define OGE_KEY_RIGHT_SHIFT     ::openGameEngine3D::Key::RightShift
#define OGE_KEY_RIGHT_CONTROL   ::openGameEngine3D::Key::RightControl
#define OGE_KEY_RIGHT_ALT       ::openGameEngine3D::Key::RightAlt
#define OGE_KEY_RIGHT_SUPER     ::openGameEngine3D::Key::RightSuper
#define OGE_KEY_MENU            ::openGameEngine3D::Key::Menu