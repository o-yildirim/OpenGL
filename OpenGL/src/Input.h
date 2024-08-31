#pragma once
#include "GLFW/glfw3.h"
#include "unordered_map";
#include "InputWrapper.h"
class Input
{
public:
	Input(GLFWwindow* window);
public:
	bool GetKeyDown(Keys key);
	bool GetKeyHeld(Keys key);
	bool GetKeyUp(Keys key);

	bool GetMouseButtonDown(MouseButtons button);
	bool GetMouseButtonHeld(MouseButtons button);
	bool GetMouseButtonUp(MouseButtons button);

	bool GetMouseScroll(MouseScroll direction);

	void Update();

private:
	static short int scrollInfo; //1 is up, -1 is down scrolling.
	static std::unordered_map<Keys, bool> m_PreviousFrameKeyStates;
	static std::unordered_map<Keys, bool> m_CurrentKeyStates;
	static std::unordered_map<MouseButtons, bool> m_PreviousFrameMouseButtonStates;
	static std::unordered_map<MouseButtons, bool> m_CurrentMouseButtonStates;

	
private:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};