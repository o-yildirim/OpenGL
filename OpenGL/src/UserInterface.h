#pragma once
#include "Shapes.h" //It is at top because it indirectly includes Renderer.h which includes glew. It must be included before glfw.
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "GameObject.h"
#include "unordered_map"
#include "Camera.h" 
#include <functional>


class UserInterface 
{
private:
	const char* glsl_version = "#version 460";
	ImGuiIO io;
	GLFWwindow* window;
	GameObject* gameObjectToDisplay;


public:
	UserInterface(GLFWwindow* window);
	void NewFrame();
	void EndFrame();
	void DrawObjectComponents();
	void Render();
	void Terminate();
	void DrawAddComponentButton();
	void DisplayComponentSelectionMenu();
	void DisplayThreeDotsPopup(Component* component);
	void DrawComponent(Component* component);

	inline void SetGameObject(GameObject* obj) { this->gameObjectToDisplay = obj; }
	inline GameObject* GetGameObject() { return this->gameObjectToDisplay; }
};