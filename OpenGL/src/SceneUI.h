#pragma once

#include "Window.h"
#include "Transform.h"
#include "ComponentUI.h"
#include "unordered_map"

class Scene;

class SceneUI 
{
private:
	static Scene* _currentScene;
	static float _offset;
	static std::unordered_map<GameObject*, bool> headers;
public:
	static void DrawSceneTree();
	static void DrawSceneObj(GameObject* obj, float margin);

	inline static void SetCurrentScene(Scene* scene) 
	{ 
		/*
		if (_currentScene != nullptr && _currentScene != scene)
		{
			delete _currentScene;
		}
		*/
		_currentScene = scene; 
	}

	inline static Scene* GetCurrentScene() { return _currentScene; }
};
