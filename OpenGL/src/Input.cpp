#include "Input.h"
#include <iostream>

std::unordered_map<Keys, bool> Input::m_PreviousFrameKeyStates;
std::unordered_map<Keys, bool> Input::m_CurrentKeyStates;

std::unordered_map<MouseButtons, bool> Input::m_PreviousFrameMouseButtonStates;
std::unordered_map<MouseButtons, bool> Input::m_CurrentMouseButtonStates;

short int Input::scrollInfo = 0;

void Input::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	scrollInfo = (int) yOffset;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		m_CurrentKeyStates[(Keys)key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		m_CurrentKeyStates[(Keys)key] = false;
	}
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		m_CurrentMouseButtonStates[(MouseButtons)button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		m_CurrentMouseButtonStates[(MouseButtons)button] = false;
	}
}

Input::Input(GLFWwindow* window)
{
	std::vector<Keys> keys = InputWrapperUtil::GetAllKeys();
	for (Keys key : keys)
	{
		this->m_PreviousFrameKeyStates[key] = false;
		this->m_CurrentKeyStates[key] = false;
	}
	glfwSetKeyCallback(window, KeyCallback);

	std::vector<MouseButtons> mouseButtons = InputWrapperUtil::GetAllMouseButtons();
	for (MouseButtons button : mouseButtons)
	{
		this->m_PreviousFrameMouseButtonStates[button] = false;
		this->m_CurrentMouseButtonStates[button] = false;
	}
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	glfwSetScrollCallback(window, MouseScrollCallback);

}

void Input::Update()
{
	this->m_PreviousFrameKeyStates = this->m_CurrentKeyStates;
	this->m_PreviousFrameMouseButtonStates = this->m_CurrentMouseButtonStates;
	this->scrollInfo = 0;
}

//For keys.
bool Input::GetKeyUp(Keys key)
{
	return (this->m_PreviousFrameKeyStates[key] && !this->m_CurrentKeyStates[key]);
}

bool Input::GetKeyDown(Keys key)
{
	return (!this->m_PreviousFrameKeyStates[key] && this->m_CurrentKeyStates[key]);
}

bool Input::GetKeyHeld(Keys key)
{
	return (this->m_PreviousFrameKeyStates[key] && this->m_CurrentKeyStates[key]);
}

//For mouse buttons.
bool Input::GetMouseButtonUp(MouseButtons button)
{
	return (this->m_PreviousFrameMouseButtonStates[button] && !this->m_CurrentMouseButtonStates[button]);
}

bool Input::GetMouseScroll(MouseScroll direction)
{
	if (direction == MouseScroll::Up)
	{
		if(this->scrollInfo == 1)
			return true;
		return false;
	}
	else //MouseScroll:Down
	{
		if (this->scrollInfo == -1)
			return true;
		return false;
	}
}

bool Input::GetMouseButtonDown(MouseButtons button)
{
	return (!this->m_PreviousFrameMouseButtonStates[button] && this->m_CurrentMouseButtonStates[button]);
}

bool Input::GetMouseButtonHeld(MouseButtons button)
{
	return (this->m_PreviousFrameMouseButtonStates[button] && this->m_CurrentMouseButtonStates[button]);
}

