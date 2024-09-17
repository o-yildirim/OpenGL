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

	static GameObject* _gameObjectToDisplay;

public:
	static void DrawObjectComponents();
	static void DrawAddComponentButton();
	static void DisplayComponentSelectionMenu();
	static void DisplayThreeDotsPopup(Component* component);
	static void DrawComponent(Component* component);

	static inline void SetGameObject(GameObject* obj) { _gameObjectToDisplay = obj; }
	static inline GameObject* GetGameObject() { return _gameObjectToDisplay; }
};