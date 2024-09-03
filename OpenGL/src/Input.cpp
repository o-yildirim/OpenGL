#include "Input.h"
#include <iostream>

std::unordered_map<Keys, bool> Input::m_PreviousFrameKeyStates;
std::unordered_map<Keys, bool> Input::m_CurrentKeyStates;

std::unordered_map<MouseButtons, bool> Input::m_PreviousFrameMouseButtonStates;
std::unordered_map<MouseButtons, bool> Input::m_CurrentMouseButtonStates;

glm::vec2 Input::m_MousePos;

short int Input::m_ScrollInfo = 0;

void Input::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	m_ScrollInfo = (int) yOffset;
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

	glfwSetCursorPosCallback(window, MousePositionCallback);

}
void Input::MousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	m_MousePos.x = xPos;
	m_MousePos.y = yPos;
}

void Input::Update()
{
	m_PreviousFrameKeyStates = m_CurrentKeyStates;
	m_PreviousFrameMouseButtonStates = m_CurrentMouseButtonStates;
	m_ScrollInfo = 0;
}

//For keys.
bool Input::GetKeyUp(Keys key)
{
	return (m_PreviousFrameKeyStates[key] && !m_CurrentKeyStates[key]);
}

bool Input::GetKeyDown(Keys key)
{
	return (!m_PreviousFrameKeyStates[key] && m_CurrentKeyStates[key]);
}

bool Input::GetKeyHeld(Keys key)
{
	return (m_PreviousFrameKeyStates[key] && m_CurrentKeyStates[key]);
}

//For mouse buttons.
bool Input::GetMouseButtonUp(MouseButtons button)
{
	return (m_PreviousFrameMouseButtonStates[button] && !m_CurrentMouseButtonStates[button]);
}

bool Input::GetMouseScroll(MouseScroll direction)
{
	if (direction == MouseScroll::Up)
	{
		if(m_ScrollInfo == 1)
			return true;
		return false;
	}
	else //MouseScroll:Down
	{
		if (m_ScrollInfo == -1)
			return true;
		return false;
	}
}

bool Input::GetMouseButtonDown(MouseButtons button)
{
	return (!m_PreviousFrameMouseButtonStates[button] && m_CurrentMouseButtonStates[button]);
}

bool Input::GetMouseButtonHeld(MouseButtons button)
{
	return (m_PreviousFrameMouseButtonStates[button] && m_CurrentMouseButtonStates[button]);
}

glm::vec2 Input::GetMousePosition()
{
	return m_MousePos;
}
