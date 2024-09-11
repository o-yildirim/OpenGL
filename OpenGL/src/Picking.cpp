#include "Picking.h"

void Picking::Update(std::vector<GameObject*> renderedObjects)
{
	if (Input::GetMouseButtonDown(MouseButtons::Left)) //TODO Burasinin icerisinin mantigini duzelt.
	{	
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = this->_camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));
			std::cout << "Clicked at " << convertedMousePos.x << ", " << convertedMousePos.y << std::endl;
			GameObject* closest = this->GetClosest(renderedObjects, convertedMousePos);

			if (closest)
			{
				if (this->_status == Picking::PickedMultipleObjects)
				{
					for (GameObject* obj : this->_pickedObjects)
					{
						if (obj == closest)
						{
							//std::cout << "Dragging multiple." << std::endl;
							return;
						}
					}
					this->_pickedObjects.clear();
					this->_initialPositionDifs.clear();
					this->_pickedObjects.push_back(closest);
					this->_status = Picking::Picked;
				}

				if (this->_pickedObjects.size() != 0)
				{
					this->_pickedObjects.clear();
					this->_initialPositionDifs.clear();
				}
				this->_pickedObjects.push_back(closest);
				this->_status = Picking::Picked;
			}
			else
			{
				this->_pickedObjects.clear();
				this->_initialPositionDifs.clear();
				this->_status = Picking::NotPicked;
				std::cout << "Not picked" << std::endl;
				//TODO remove boundaries.
			}
		
	}
	else if(Input::GetMouseButtonHeld(MouseButtons::Left))
	{
		if (this->_status == Picking::NotPicked) //Then starts to selecting an area.
		{
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = this->_camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));
			this->_areaStartPoint = convertedMousePos;
			this->_status = Picking::SelectingArea;
		}
		else if (this->_status == Picking::Picked || this->_status == Picking::PickedMultipleObjects)
		{
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = this->_camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));

			for (GameObject* pickedObj : this->_pickedObjects)
			{
				glm::vec3 objPos = pickedObj->GetComponent<Transform>()->position;
				glm::vec2 initialPositionDif(convertedMousePos.x - objPos.x, convertedMousePos.y - objPos.y);
				this->_initialPositionDifs.push_back(initialPositionDif);
			}
			this->_status = Picking::Dragging;
		}
		else if (this->_status == Picking::Dragging)
		{
			
			//Keep repositioning untill mouse is released.
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = this->_camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));

			for(int i = 0; i < this->_pickedObjects.size(); i++)
			{
				Transform* objTransform = this->_pickedObjects[i]->GetComponent<Transform>();
				glm::vec3 objPos = objTransform->position;
				glm::vec3 newPos(convertedMousePos.x - this->_initialPositionDifs[i].x, convertedMousePos.y - this->_initialPositionDifs[i].y, 0.0f);
				objTransform->position = newPos;
				
			}
		}
	}
	else if(Input::GetMouseButtonUp(MouseButtons::Left))
	{
		if (this->_status == Picking::Dragging)
		{
			if (this->_pickedObjects.size() == 1)
			{
				this->_status = Picking::Picked; //Stopped dragging but still picked.
			}
			else if (this->_pickedObjects.size() > 1)
			{
				this->_status = Picking::PickedMultipleObjects;
			}
		}
		else if (this->_status == Picking::SelectingArea)
		{
			this->_pickedObjects.clear();
			this->_initialPositionDifs.clear();

			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = this->_camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));
			this->_pickedObjects = this->GetAllWithinSelectedArea(renderedObjects,this->_areaStartPoint,glm::vec2(convertedMousePos.x, convertedMousePos.y));
			
			
			
			if (this->_pickedObjects.size() == 0)
			{
				this->_status = Picking::NotPicked;
			}
			else if (this->_pickedObjects.size() == 1)
			{
				this->_status = Picking::Picked;
			}
			else
			{
				this->_status = Picking::PickedMultipleObjects;
			}
		}
	}
}

std::vector<GameObject*> Picking::GetAllWithinSelectedArea(std::vector<GameObject*> renderedObjects, glm::vec2 startPos, glm::vec2 endPos)
{
	
	//std::cout << "Start: " << startPos.x << ", " << startPos.y << std::endl;
	//std::cout << "End: " << endPos.x << ", " << endPos.y << std::endl;
	
	std::vector<GameObject*> objectsInsideRect;
	glm::vec2 centerPos((startPos.x + endPos.x) / 2.0f, (startPos.y + endPos.y) / 2.0f);
	float xLen = glm::abs(startPos.x - endPos.x);
	float yLen = glm::abs(startPos.y - endPos.y);
	for (GameObject* obj : renderedObjects)
	{
		glm::vec3 objPos = obj->GetComponent<Transform>()->position;
		if (objPos.x > centerPos.x - xLen / 2.0f && objPos.x < centerPos.x + xLen / 2.0f)
		{
			if (objPos.y < centerPos.y + yLen / 2.0f && objPos.y > centerPos.y - yLen / 2.0f)
			{
				objectsInsideRect.push_back(obj);
			}
		}

	}
	return objectsInsideRect;
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