#pragma once
#include "Scene.h"

class SceneUI 
{
private:
	static Scene* _currentScene;
	static float _offset;
public:
	static void DrawSceneTree();
	static void DrawSceneObj(GameObject* obj);

	inline static void SetCurrentScene(Scene* scene) { _currentScene = scene; }
	inline static Scene* GetCurrentScene() { return _currentScene; }
};
