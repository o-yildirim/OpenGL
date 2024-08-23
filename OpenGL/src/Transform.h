#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Component.h"

class Transform : public Component
{

private:
	glm::mat4 modelMatrix;
private:
	void ResetModelMatrix();

public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	Transform();
	~Transform();
	void Translate(glm::vec3 toPosition);
	void Rotate(float angleInDegrees, glm::vec3 rotationAxis);
	void Scale(glm::vec3 newScale);
	void Update();
	glm::mat4 getModelMatrix();

};