#include "Picking.h"

std::vector<GameObject*> Picking::_pickedObjects;
std::vector<glm::vec2> Picking::_initialPositionDifs;
glm::vec2 Picking::_areaStartPoint;

Camera* Picking::_camera = nullptr;
Picking::PickingStatus Picking::_status = Picking::NotPicked;

void Picking::Update(std::vector<GameObject*> renderedObjects)
{
	if (Input::GetMouseButtonDown(MouseButtons::Left)) //TODO Burasinin icerisinin mantigini duzelt.
	{	
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = _camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));
			//std::cout << "Clicked at " << convertedMousePos.x << ", " << convertedMousePos.y << std::endl;
			GameObject* closest = GetClosest(renderedObjects, convertedMousePos);

			if (closest)
			{
				if (_status == Picking::PickedMultipleObjects)
				{
					for (GameObject* obj : _pickedObjects)
					{
						if (obj == closest)
						{
							//std::cout << "Dragging multiple." << std::endl;
							return;
						}
					}
					_pickedObjects.clear();
					_initialPositionDifs.clear();
					_pickedObjects.push_back(closest);
					_status = PickingStatus::Picked;
				}

				if (_pickedObjects.size() != 0)
				{
					_pickedObjects.clear();
					_initialPositionDifs.clear();
				}
				_pickedObjects.push_back(closest);
				_status = Picking::Picked;
			}
			else
			{
				_pickedObjects.clear();
				_initialPositionDifs.clear();
				_status = Picking::NotPicked;
				//std::cout << "Not picked" << std::endl;
			}
		
	}
	else if(Input::GetMouseButtonHeld(MouseButtons::Left))
	{
		if (_status == Picking::NotPicked) //Then starts to selecting an area.
		{
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = _camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));
			_areaStartPoint = convertedMousePos;
			_status = Picking::SelectingArea;
		}
		else if (_status == Picking::Picked || _status == Picking::PickedMultipleObjects)
		{
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = _camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));

			for (GameObject* pickedObj : _pickedObjects)
			{
				glm::vec3 objPos = pickedObj->GetComponent<Transform>()->worldPosition;
				glm::vec2 initialPositionDif(convertedMousePos.x - objPos.x, convertedMousePos.y - objPos.y);
				_initialPositionDifs.push_back(initialPositionDif);
			}
			_status = Picking::Dragging;
		}
		else if (_status == Picking::Dragging)
		{
			
			//Keep repositioning untill mouse is released.
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = _camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));

			for(int i = 0; i < _pickedObjects.size(); i++)
			{
				
				Transform* objTransform = _pickedObjects[i]->GetComponent<Transform>();
				glm::vec3 objPos = objTransform->worldPosition;
				glm::vec3 newPos(convertedMousePos.x - _initialPositionDifs[i].x, convertedMousePos.y - _initialPositionDifs[i].y, 0.0f);
				glm::vec3 newLocalPos = objTransform->WorldToLocalPosition(newPos);
				objTransform->Translate(newLocalPos);

				
			}
		}
	}
	else if(Input::GetMouseButtonUp(MouseButtons::Left))
	{
		if (_status == Picking::Dragging)
		{
			if (_pickedObjects.size() == 1)
			{
				_status = Picking::Picked; //Stopped dragging but still picked.
			}
			else if (_pickedObjects.size() > 1)
			{
				_status = Picking::PickedMultipleObjects;
			}
		}
		else if (_status == Picking::SelectingArea)
		{
			_pickedObjects.clear();
			_initialPositionDifs.clear();

			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec3 convertedMousePos = _camera->ConvertScreenToWorld(glm::vec3(mousePos.x, mousePos.y, 0.0f));
			_pickedObjects = GetAllWithinSelectedArea(renderedObjects,_areaStartPoint,glm::vec2(convertedMousePos.x, convertedMousePos.y));
			
			
			
			if (_pickedObjects.size() == 0)
			{
				_status = Picking::NotPicked;
			}
			else if (_pickedObjects.size() == 1)
			{
				_status = Picking::Picked;
			}
			else
			{
				_status = Picking::PickedMultipleObjects;
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
		glm::vec3 objPos = obj->GetComponent<Transform>()->localPosition;
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