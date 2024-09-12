#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "Shapes.h"
#include "Input.h"
#include "Window.h"
#include <vector>

class Picking
{
	enum PickingStatus
	{
		NotPicked,
		Picked,
		Dragging,
		SelectingArea,
		PickedMultipleObjects
	};

private:
	std::vector<GameObject*> _pickedObjects;
	std::vector<glm::vec2> _initialPositionDifs;
	glm::vec2 _areaStartPoint;

	Camera* _camera = nullptr;
	enum PickingStatus _status = Picking::NotPicked;
public:
	void Update(std::vector<GameObject*> renderedObjects);
	GameObject* GetClosest(std::vector<GameObject*> renderedObjects, glm::vec2 point);
	std::vector<GameObject*> GetAllWithinSelectedArea(std::vector<GameObject*> renderedObjects, glm::vec2 startPos, glm::vec2 endPos);
	inline std::vector<GameObject*> GetSelectedObjects() { return this->_pickedObjects; }
	inline void SetCamera(Camera* cam) { this->_camera = cam; }
};