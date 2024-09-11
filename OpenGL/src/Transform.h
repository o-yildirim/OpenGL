#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Component.h"

class Transform : public Component
{
private:
	glm::mat4 modelMatrix;
	float inputBoxLength = 70.0f;
private:
	void ResetModelMatrix();

public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 forward;
public:
	Transform();
	~Transform();
	void Translate(glm::vec3 toPosition);
	void Rotate(float angleInDegrees, glm::vec3 rotationAxis);
	void Scale(glm::vec3 newScale);
	void Update();
	glm::mat4 getModelMatrix();

	void DisplayComponent() override;
	//inline GameObject* GetParent() { return this->parent; }
	//inline void SetParent(GameObject* parent) { this->parent = parent; }
private:
	void UpdateDirectionVectors();
};