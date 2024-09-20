#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Component.h"
#include "GameObject.h"

class Transform : public Component
{
private:
	glm::mat4 localModelMatrix;
	glm::mat4 worldModelMatrix;
	float inputBoxLength = 70.0f;
	bool isDirty;
private:
	void ResetModelMatrix();
	void GetRootHelper(Transform* obj, Transform*& root);
	glm::mat4 GetWorldTransformHelper(Transform* obj);
	void MarkDirty();

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

	glm::mat4& GetLocalModelMatrix();
	glm::mat4& GetWorldModelMatrix();//Cumulative transform multiplied using all parents, grandparents etc.
	glm::mat4 ComputeWorldTransformationMatrix();
	glm::vec3 GetWorldPosition();
	glm::vec3 GetWorldScale();
	glm::quat GetWorldRotationQuaternion();
	glm::vec3 GetWorldRotationEuler();

	glm::vec3 WorldToLocalPosition(const glm::vec3& worldPos) const;
	glm::vec3 WorldToLocalRotation(const glm::vec3& worldRot) const;
	glm::vec3 WorldToLocalScale(const glm::vec3& worldScale) const;
	void DisplayComponent() override;

	inline void SetRotation(glm::vec3 rot)
	{
		this->localRotation = rot;
		this->MarkDirty();
	}

	//inline GameObject* GetParent() { return this->parent; }
	//inline void SetParent(GameObject* parent) { this->parent = parent; }
private:
	void UpdateDirectionVectors();
};