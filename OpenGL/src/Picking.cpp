#include "Picking.h"
#include "Shape.h"
#include "Input.h"

void Picking::Update(std::vector<GameObject*> renderedObjects)
{
	if (Input::GetMouseButtonDown(MouseButtons::Left))
	{
		std::cout << "Clicked at " << Input::GetMousePosition().x << ", " << Input::GetMousePosition().y << std::endl;
		this->pickedObj = this->GetClosest(renderedObjects, Input::GetMousePosition());
	}
}

GameObject* Picking::GetClosest(std::vector<GameObject*> renderedObjects, glm::vec2 point)
{
	GameObject* clickedObj = nullptr;
	for (GameObject* object : renderedObjects)
	{
		Shape* shape = object->GetComponent<Shape>();
		if(shape)
		{
			if (shape->isInside(point.x, point.y))
			{
				clickedObj = object;
			}
		}
	}
	return clickedObj;
}