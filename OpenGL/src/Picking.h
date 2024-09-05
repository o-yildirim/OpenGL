#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "Shape.h"
#include "Input.h"
#include "Window.h"
class Picking
{
	enum PickingStatus
	{
		NotPicked,
		Picked,
		Dragging
	};

private:
	GameObject* _pickedObj= nullptr;
	glm::vec2 _initialPositionDif;

	Camera* _camera = nullptr;
	enum PickingStatus _status = Picking::NotPicked;
public:
	void Update(std::vector<GameObject*> renderedObjects);
	GameObject* GetClosest(std::vector<GameObject*> renderedObjects, glm::vec2 point);
	inline GameObject* GetSelectedObject() { return this->_pickedObj; }
	inline void SetCamera(Camera* cam) { this->_camera = cam; }
};