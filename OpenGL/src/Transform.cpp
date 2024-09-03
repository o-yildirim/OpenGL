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

void Transform::DisplayComponent()
{
    ImGui::Begin("Transform");
    //Position
    ImGui::PushItemWidth(this->inputBoxLength);
    ImGui::Text("Position");
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##posX", &this->position.x, 0.0f, 0.0f, "%.3f");

    ImGui::SameLine();

    ImGui::Text("Y:");
    ImGui::SameLine();

    ImGui::InputFloat("##posY", &this->position.y, 0.0f, 0.0f, "%.3f");
    ImGui::SameLine();

    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##posZ", &this->position.z, 0.0f, 0.0f, "%.3f");

    //Rotation
    ImGui::Text("Rotation");
    ImGui::Text("X:");
    ImGui::SameLine();

    ImGui::InputFloat("##rotX", &this->rotation.x, 0.0f, 0.0f, "%.3f");
    ImGui::SameLine();

    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##rotY", &this->rotation.y, 0.0f, 0.0f, "%.3f");
    ImGui::SameLine();

    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##rotZ", &this->rotation.z, 0.0f, 0.0f, "%.3f");

    //Scale
    ImGui::Text("Scale");
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::InputFloat("##scaleX", &this->scale.x, 0.0f, 0.0f, "%.3f");
    ImGui::SameLine();

    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::InputFloat("##scaleY", &this->scale.y, 0.0f, 0.0f, "%.3f");
    ImGui::SameLine();

    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::InputFloat("##scaleZ", &this->scale.z, 0.0f, 0.0f, "%.3f");
    ImGui::PopItemWidth();
}