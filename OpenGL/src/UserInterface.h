#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "GameObject.h"

class UserInterface 
{
private:
	const char* glsl_version = "#version 460";
	ImGuiIO io;
	GLFWwindow* window;
	GameObject* gameObjectToDisplay; //TODO Might change to gameobject

public:
	UserInterface(GLFWwindow* window);
	void NewFrame();
	void EndFrame();
	void DrawObjectComponents();
	void Render();
	void Terminate();

	inline void SetGameObject(GameObject* obj) { this->gameObjectToDisplay = obj; }
	inline GameObject* GetGameObject() { return this->gameObjectToDisplay; }
};