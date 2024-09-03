#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"
class Picking
{
private:
	GameObject* pickedObj= nullptr;

public:
	void Update(std::vector<GameObject*> renderedObjects);
	GameObject* GetClosest(std::vector<GameObject*> renderedObjects, glm::vec2 point);
	inline GameObject* GetSelectedObject() { return this->pickedObj; }
};