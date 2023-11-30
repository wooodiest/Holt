#pragma once

namespace Holt
{
	typedef enum class KeyCode : uint16_t
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
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define HL_KEY_SPACE           ::Holt::Key::Space
#define HL_KEY_APOSTROPHE      ::Holt::Key::Apostrophe    /* ' */
#define HL_KEY_COMMA           ::Holt::Key::Comma         /* , */
#define HL_KEY_MINUS           ::Holt::Key::Minus         /* - */
#define HL_KEY_PERIOD          ::Holt::Key::Period        /* . */
#define HL_KEY_SLASH           ::Holt::Key::Slash         /* / */
#define HL_KEY_0               ::Holt::Key::D0
#define HL_KEY_1               ::Holt::Key::D1
#define HL_KEY_2               ::Holt::Key::D2
#define HL_KEY_3               ::Holt::Key::D3
#define HL_KEY_4               ::Holt::Key::D4
#define HL_KEY_5               ::Holt::Key::D5
#define HL_KEY_6               ::Holt::Key::D6
#define HL_KEY_7               ::Holt::Key::D7
#define HL_KEY_8               ::Holt::Key::D8
#define HL_KEY_9               ::Holt::Key::D9
#define HL_KEY_SEMICOLON       ::Holt::Key::Semicolon     /* ; */
#define HL_KEY_EQUAL           ::Holt::Key::Equal         /* = */
#define HL_KEY_A               ::Holt::Key::A
#define HL_KEY_B               ::Holt::Key::B
#define HL_KEY_C               ::Holt::Key::C
#define HL_KEY_D               ::Holt::Key::D
#define HL_KEY_E               ::Holt::Key::E
#define HL_KEY_F               ::Holt::Key::F
#define HL_KEY_G               ::Holt::Key::G
#define HL_KEY_H               ::Holt::Key::H
#define HL_KEY_I               ::Holt::Key::I
#define HL_KEY_J               ::Holt::Key::J
#define HL_KEY_K               ::Holt::Key::K
#define HL_KEY_L               ::Holt::Key::L
#define HL_KEY_M               ::Holt::Key::M
#define HL_KEY_N               ::Holt::Key::N
#define HL_KEY_O               ::Holt::Key::O
#define HL_KEY_P               ::Holt::Key::P
#define HL_KEY_Q               ::Holt::Key::Q
#define HL_KEY_R               ::Holt::Key::R
#define HL_KEY_S               ::Holt::Key::S
#define HL_KEY_T               ::Holt::Key::T
#define HL_KEY_U               ::Holt::Key::U
#define HL_KEY_V               ::Holt::Key::V
#define HL_KEY_W               ::Holt::Key::W
#define HL_KEY_X               ::Holt::Key::X
#define HL_KEY_Y               ::Holt::Key::Y
#define HL_KEY_Z               ::Holt::Key::Z
#define HL_KEY_LEFT_BRACKET    ::Holt::Key::LeftBracket   /* [ */
#define HL_KEY_BACKSLASH       ::Holt::Key::Backslash     /* \ */
#define HL_KEY_RIGHT_BRACKET   ::Holt::Key::RightBracket  /* ] */
#define HL_KEY_GRAVE_ACCENT    ::Holt::Key::GraveAccent   /* ` */
#define HL_KEY_WORLD_1         ::Holt::Key::World1        /* non-US #1 */
#define HL_KEY_WORLD_2         ::Holt::Key::World2        /* non-US #2 */

/* Function keys */
#define HL_KEY_ESCAPE          ::Holt::Key::Escape
#define HL_KEY_ENTER           ::Holt::Key::Enter
#define HL_KEY_TAB             ::Holt::Key::Tab
#define HL_KEY_BACKSPACE       ::Holt::Key::Backspace
#define HL_KEY_INSERT          ::Holt::Key::Insert
#define HL_KEY_DELETE          ::Holt::Key::Delete
#define HL_KEY_RIGHT           ::Holt::Key::Right
#define HL_KEY_LEFT            ::Holt::Key::Left
#define HL_KEY_DOWN            ::Holt::Key::Down
#define HL_KEY_UP              ::Holt::Key::Up
#define HL_KEY_PAGE_UP         ::Holt::Key::PageUp
#define HL_KEY_PAGE_DOWN       ::Holt::Key::PageDown
#define HL_KEY_HOME            ::Holt::Key::Home
#define HL_KEY_END             ::Holt::Key::End
#define HL_KEY_CAPS_LOCK       ::Holt::Key::CapsLock
#define HL_KEY_SCROLL_LOCK     ::Holt::Key::ScrollLock
#define HL_KEY_NUM_LOCK        ::Holt::Key::NumLock
#define HL_KEY_PRINT_SCREEN    ::Holt::Key::PrintScreen
#define HL_KEY_PAUSE           ::Holt::Key::Pause
#define HL_KEY_F1              ::Holt::Key::F1
#define HL_KEY_F2              ::Holt::Key::F2
#define HL_KEY_F3              ::Holt::Key::F3
#define HL_KEY_F4              ::Holt::Key::F4
#define HL_KEY_F5              ::Holt::Key::F5
#define HL_KEY_F6              ::Holt::Key::F6
#define HL_KEY_F7              ::Holt::Key::F7
#define HL_KEY_F8              ::Holt::Key::F8
#define HL_KEY_F9              ::Holt::Key::F9
#define HL_KEY_F10             ::Holt::Key::F10
#define HL_KEY_F11             ::Holt::Key::F11
#define HL_KEY_F12             ::Holt::Key::F12
#define HL_KEY_F13             ::Holt::Key::F13
#define HL_KEY_F14             ::Holt::Key::F14
#define HL_KEY_F15             ::Holt::Key::F15
#define HL_KEY_F16             ::Holt::Key::F16
#define HL_KEY_F17             ::Holt::Key::F17
#define HL_KEY_F18             ::Holt::Key::F18
#define HL_KEY_F19             ::Holt::Key::F19
#define HL_KEY_F20             ::Holt::Key::F20
#define HL_KEY_F21             ::Holt::Key::F21
#define HL_KEY_F22             ::Holt::Key::F22
#define HL_KEY_F23             ::Holt::Key::F23
#define HL_KEY_F24             ::Holt::Key::F24
#define HL_KEY_F25             ::Holt::Key::F25

/* Keypad */
#define HL_KEY_KP_0            ::Holt::Key::KP0
#define HL_KEY_KP_1            ::Holt::Key::KP1
#define HL_KEY_KP_2            ::Holt::Key::KP2
#define HL_KEY_KP_3            ::Holt::Key::KP3
#define HL_KEY_KP_4            ::Holt::Key::KP4
#define HL_KEY_KP_5            ::Holt::Key::KP5
#define HL_KEY_KP_6            ::Holt::Key::KP6
#define HL_KEY_KP_7            ::Holt::Key::KP7
#define HL_KEY_KP_8            ::Holt::Key::KP8
#define HL_KEY_KP_9            ::Holt::Key::KP9
#define HL_KEY_KP_DECIMAL      ::Holt::Key::KPDecimal
#define HL_KEY_KP_DIVIDE       ::Holt::Key::KPDivide
#define HL_KEY_KP_MULTIPLY     ::Holt::Key::KPMultiply
#define HL_KEY_KP_SUBTRACT     ::Holt::Key::KPSubtract
#define HL_KEY_KP_ADD          ::Holt::Key::KPAdd
#define HL_KEY_KP_ENTER        ::Holt::Key::KPEnter
#define HL_KEY_KP_EQUAL        ::Holt::Key::KPEqual

#define HL_KEY_LEFT_SHIFT      ::Holt::Key::LeftShift
#define HL_KEY_LEFT_CONTROL    ::Holt::Key::LeftControl
#define HL_KEY_LEFT_ALT        ::Holt::Key::LeftAlt
#define HL_KEY_LEFT_SUPER      ::Holt::Key::LeftSuper
#define HL_KEY_RIGHT_SHIFT     ::Holt::Key::RightShift
#define HL_KEY_RIGHT_CONTROL   ::Holt::Key::RightControl
#define HL_KEY_RIGHT_ALT       ::Holt::Key::RightAlt
#define HL_KEY_RIGHT_SUPER     ::Holt::Key::RightSuper
#define HL_KEY_MENU            ::Holt::Key::Menu