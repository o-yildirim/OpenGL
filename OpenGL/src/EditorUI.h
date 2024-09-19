#pragma once
#include <iostream>
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

class EditorUI
{
private:
	static const char* _glsl_version;
	static int framerate;
	//static ImGuiIO& _io;
public:
	static void Init(GLFWwindow* window);
	static void NewFrame();
	static void EndFrame();
	static void Render();
	static void Terminate();
	static void DisplayFrameRate();
	inline static void UpdateFramerate(int newFramerate) { framerate = newFramerate; }
};