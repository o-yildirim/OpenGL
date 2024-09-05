#include "Picking.h"

void Picking::Update(std::vector<GameObject*> renderedObjects)
{
	if (Input::GetMouseButtonDown(MouseButtons::Left))
	{
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = this->_camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));
			std::cout << "Clicked at " << convertedMousePos.x << ", " << convertedMousePos.y << std::endl;
			this->_pickedObj = this->GetClosest(renderedObjects, convertedMousePos);
			if (this->_pickedObj)
			{
				this->_status = Picking::Picked;
				//TODO render boundaries.
			}
			else
			{
				this->_status = Picking::NotPicked;
				//TODO remove boundaries.
			}
	}
	else if(Input::GetMouseButtonHeld(MouseButtons::Left))
	{
		if (this->_pickedObj != nullptr)
		{
			if (this->_status == Picking::Picked)
			{
				//TODO compute initial pos differences
				glm::vec2 mousePos = Input::GetMousePosition();
				glm::vec3 convertedMousePos = this->_camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));


				glm::vec3 objPos = this->_pickedObj->GetComponent<Transform>()->position;
				this->_initialPositionDif = glm::vec2(convertedMousePos.x - objPos.x, convertedMousePos.y - objPos.y);
				this->_status = Picking::Dragging;
			}
			else if (this->_status == Picking::Dragging)
			{
				//TODO Keep repositioning untill mouse is released.
				glm::vec2 mousePos = Input::GetMousePosition();
				glm::vec3 convertedMousePos = this->_camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));

				Transform* objTransform = this->_pickedObj->GetComponent<Transform>();
				glm::vec3 objPos = objTransform->position;
				glm::vec3 newPos(convertedMousePos.x - this->_initialPositionDif.x, convertedMousePos.y - this->_initialPositionDif.y, 0.0f);
				objTransform->position = newPos;

			}		
		}
	}
	else if(Input::GetMouseButtonUp(MouseButtons::Left))
	{
		if (this->_status == Picking::Dragging)
		{
			this->_status = Picking::Picked; //Stopped dragging but still picked.
		}
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