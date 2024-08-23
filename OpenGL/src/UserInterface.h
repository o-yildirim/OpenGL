#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "Transform.h"

class UserInterface 
{
private:
	const char* glsl_version = "#version 460";
	ImGuiIO io;
	GLFWwindow* window;
	Transform* transformToDisplay; //TODO Might change to gameobject

public:
	UserInterface(GLFWwindow* window);

	void Init();
	void NewFrame();
	void EndFrame();
	void DrawTransformWindow();
	void Render();
	void Terminate();

	inline void SetTransform(Transform* transform) { this->transformToDisplay = transform; }
	inline Transform GetTransform() { return *this->transformToDisplay; }
};