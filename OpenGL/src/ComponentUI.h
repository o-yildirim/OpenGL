#pragma once
#include "Shapes.h" 
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "GameObject.h"
#include "unordered_map"
#include "Camera.h" 
#include <functional>


class ComponentUI 
{
private:
	static const char* _glsl_version;
	//static ImGuiIO& _io;
	static GameObject* _gameObjectToDisplay;


public:
	static void Init(GLFWwindow* window);
	static void NewFrame();
	static void EndFrame();
	static void DrawObjectComponents();
	static void Render();
	static void Terminate();
	static void DrawAddComponentButton();
	static void DisplayComponentSelectionMenu();
	static void DisplayThreeDotsPopup(Component* component);
	static void DrawComponent(Component* component);

	static inline void SetGameObject(GameObject* obj) { _gameObjectToDisplay = obj; }
	static inline GameObject* GetGameObject() { return _gameObjectToDisplay; }
};