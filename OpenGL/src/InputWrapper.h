#include "GLFW/glfw3.h">

enum class Keys
{
	Space = GLFW_KEY_SPACE,
	Escape = GLFW_KEY_ESCAPE,
	Enter = GLFW_KEY_ENTER,
	LeftArrow = GLFW_KEY_LEFT,
	RightArrow = GLFW_KEY_RIGHT,
	UpArrow = GLFW_KEY_UP,
	DownArrow = GLFW_KEY_DOWN,

	F1 = GLFW_KEY_F1,
	F2 = GLFW_KEY_F2,
	F3 = GLFW_KEY_F3,
	F4 = GLFW_KEY_F4,
	F5 = GLFW_KEY_F5,
	F6 = GLFW_KEY_F6,
	F7 = GLFW_KEY_F7,
	F8 = GLFW_KEY_F8,
	F9 = GLFW_KEY_F9,
	F10 = GLFW_KEY_F10,
	F11 = GLFW_KEY_F11,
	F12 = GLFW_KEY_F12,

	A = GLFW_KEY_A,
	B = GLFW_KEY_B,
	C = GLFW_KEY_C,
	D = GLFW_KEY_D,
	E = GLFW_KEY_E,
	F = GLFW_KEY_F,
	G = GLFW_KEY_G,
	H = GLFW_KEY_H,
	I = GLFW_KEY_I,
	J = GLFW_KEY_J,
	K = GLFW_KEY_K,
	L = GLFW_KEY_L,
	M = GLFW_KEY_M,
	N = GLFW_KEY_N,
	O = GLFW_KEY_O,
	P = GLFW_KEY_P,
	Q = GLFW_KEY_Q,
	R = GLFW_KEY_R,
	S = GLFW_KEY_S,
	T = GLFW_KEY_T,
	U = GLFW_KEY_U,
	V = GLFW_KEY_V,
	W = GLFW_KEY_W,
	X = GLFW_KEY_X,
	Y = GLFW_KEY_Y,
	Z = GLFW_KEY_Z
};

enum class MouseButtons
{
	Left = GLFW_MOUSE_BUTTON_LEFT,
	Middle = GLFW_MOUSE_BUTTON_MIDDLE,
	Right = GLFW_MOUSE_BUTTON_RIGHT,
	
	
};

enum class MouseScroll
{
	Up = 1,
	Down = -1,

};

class InputWrapperUtil
{
public:
	inline static std::vector<Keys> GetAllKeys()
	{
		return std::vector<Keys>
		{
			Keys::Space, Keys::Escape, Keys::Enter, Keys::LeftArrow, Keys::RightArrow, Keys::UpArrow, Keys::DownArrow,
			Keys::F1, Keys::F2, Keys::F3, Keys::F4, Keys::F5, Keys::F6, Keys::F7, Keys::F8, Keys::F9, Keys::F10, Keys::F11, Keys::F12,
			Keys::A, Keys::B, Keys::C, Keys::D, Keys::E, Keys::F, Keys::G, Keys::H, Keys::I, Keys::J, Keys::K,
			Keys::L, Keys::M, Keys::N, Keys::O, Keys::P, Keys::Q, Keys::R, Keys::S, Keys::T, Keys::U, Keys::V, Keys::W, Keys::X, Keys::Y, Keys::Z
		};
	}

	inline static std::vector<MouseButtons> GetAllMouseButtons()
	{
		return std::vector<MouseButtons>
		{
			MouseButtons::Left, MouseButtons::Middle, MouseButtons::Right
		};
	}

	inline static std::vector<MouseScroll> GetAllMouseScrolls()
	{
		return std::vector<MouseScroll>
		{
			MouseScroll::Up, MouseScroll::Down
		};
	}



};