#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Component.h"
#include "GameObject.h"

class Transform : public Component
{
private:
	glm::mat4 modelMatrix;
	float inputBoxLength = 70.0f;
private:
	void ResetModelMatrix();
	void GetRootHelper(Transform* obj, Transform*& root);
	glm::mat4 GetWorldTransformHelper(Transform* obj);

public:
	glm::vec3 localPosition;
	glm::vec3 localRotation;
	glm::vec3 localScale;

	glm::vec3 worldPosition;
	glm::vec3 worldRotation;
	glm::vec3 worldScale;

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

	Transform* GetRoot();

	glm::mat4& GetModelMatrix();
	glm::mat4 GetWorldTransformationMatrix();//Cumulative transform multiplied using all parents, grandparents etc.
	glm::vec3 GetWorldPosition(const glm::mat4& transformationMatrix);
	glm::vec3 GetWorldScale(const glm::mat4& transformationMatrix);
	glm::quat GetWorldRotationQuaternion(const glm::mat4& transformationMatrix);
	glm::vec3 GetWorldRotationEuler(const glm::mat4& transform);

	void DisplayComponent() override;
	//inline GameObject* GetParent() { return this->parent; }
	//inline void SetParent(GameObject* parent) { this->parent = parent; }
private:
	void UpdateDirectionVectors();
};