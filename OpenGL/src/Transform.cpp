#include "Transform.h"
#include "Window.h"

Transform::Transform()
{
	this->modelMatrix = glm::mat4(1.0f);

	glm::vec3 center = Window::GetCenter();
	this->position = glm::vec3(center.x, center.y, 0.0f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
}


Transform::~Transform()
{
 //Currently no dynamic allocation, nothing to delete.
}

void Transform::Translate(glm::vec3 toPosition)
{
	this->ResetModelMatrix();

	this->position = toPosition;
	this->modelMatrix = glm::translate(this->modelMatrix, this->position);
}

void Transform::Rotate(float angle,glm::vec3 axisToRotateAround)
{
	this->ResetModelMatrix();

	for (int i = 0; i < 3; i++)
	{
		if (axisToRotateAround[i] == 1)
		{
			this->rotation[i] += angle;
			break;
		}
	}

	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x),glm::vec3(1,0,0));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0, 1, 0));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0, 0, 1));
}

void Transform::Scale(glm::vec3 newScale)
{
	this->ResetModelMatrix();

	this->scale = newScale;
	this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
}

void Transform::Update()
{
	this->ResetModelMatrix();

	this->modelMatrix = glm::translate(this->modelMatrix, this->position);
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x), glm::vec3(1, 0, 0));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0, 1, 0));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0, 0, 1));
	this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
}

void Transform::ResetModelMatrix()
{
	this->modelMatrix = glm::mat4(1.0f);
}

glm::mat4 Transform::getModelMatrix()
{
	return this->modelMatrix;
}