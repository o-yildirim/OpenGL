#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "Shapes.h"
#include "Input.h"
#include "Window.h"
#include <vector>

class Scene;

class Picking
{
	

private:
	static std::vector<GameObject*> _pickedObjects;
	static std::vector<glm::vec2> _initialPositionDifs;
	static glm::vec2 _areaStartPoint;

	enum PickingStatus
	{
		NotPicked,
		Picked,
		Dragging,
		SelectingArea,
		PickedMultipleObjects
	};
	static Camera* _camera;
	static PickingStatus _status;
public:
	
	static void Update(Scene* scene);
	static GameObject* GetClosest(std::vector<GameObject*> renderedObjects, glm::vec2 point);
	static std::vector<GameObject*> GetAllWithinSelectedArea(std::vector<GameObject*> renderedObjects, glm::vec2 startPos, glm::vec2 endPos);
	inline static std::vector<GameObject*> GetSelectedObjects() { return _pickedObjects; }
	inline static void SetCamera(Camera* cam) { if(cam != nullptr) _camera = cam; }
};