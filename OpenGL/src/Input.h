#pragma once
#include "GLFW/glfw3.h"
#include "unordered_map";
#include "InputWrapper.h"
#include "glm/glm.hpp"
class Input
{
public:
	
public:
	static void Init(GLFWwindow* window);
	static bool GetKeyDown(Keys key);
	static bool GetKeyHeld(Keys key);
	static bool GetKeyUp(Keys key);

	static bool GetMouseButtonDown(MouseButtons button);
	static bool GetMouseButtonHeld(MouseButtons button);
	static bool GetMouseButtonUp(MouseButtons button);

	static bool GetMouseScroll(MouseScroll direction);
	static glm::vec2 GetMousePosition();

	static void Update();

private:
	static short int m_ScrollInfo; //1 is up, -1 is down scrolling.
	static glm::vec2 m_MousePos;
	static std::unordered_map<Keys, bool> m_PreviousFrameKeyStates;
	static std::unordered_map<Keys, bool> m_CurrentKeyStates;
	static std::unordered_map<MouseButtons, bool> m_PreviousFrameMouseButtonStates;
	static std::unordered_map<MouseButtons, bool> m_CurrentMouseButtonStates;

	
private:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos);
};