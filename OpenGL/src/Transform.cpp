#include "Transform.h"
#include "Window.h"


Transform::Transform()
{
    this->_className = "Transform";

	this->modelMatrix = glm::mat4(1.0f);

	glm::vec3 center = Window::GetCenter();
	this->localPosition = glm::vec3(center.x, center.y, 0.0f);
	this->localRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->localScale = glm::vec3(1.0f, 1.0f, 1.0f);
    this->UpdateDirectionVectors();
}


Transform::~Transform()
{
 //Currently no dynamic allocation, nothing to delete.
}

void Transform::Translate(glm::vec3 toPosition)
{
	this->ResetModelMatrix();

	this->localPosition = toPosition;
	this->modelMatrix = glm::translate(this->modelMatrix, this->localPosition);
}

void Transform::Rotate(float angle,glm::vec3 axisToRotateAround)
{
	this->ResetModelMatrix();

	for (int i = 0; i < 3; i++)
	{
		if (axisToRotateAround[i] == 1)
		{
			this->localRotation[i] += angle;
			break;
		}
	}

	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->localRotation.x),glm::vec3(1,0,0));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->localRotation.y), glm::vec3(0, 1, 0));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->localRotation.z), glm::vec3(0, 0, 1));


    
}

void Transform::Scale(glm::vec3 newScale)
{
	this->ResetModelMatrix();

	this->localScale = newScale;
	this->modelMatrix = glm::scale(this->modelMatrix, this->localScale);
}

void Transform::Update()
{
	this->ResetModelMatrix();

	this->modelMatrix = glm::translate(this->modelMatrix, this->localPosition);
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->localRotation.x), glm::vec3(1, 0, 0));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->localRotation.y), glm::vec3(0, 1, 0));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->localRotation.z), glm::vec3(0, 0, 1));
	this->modelMatrix = glm::scale(this->modelMatrix, this->localScale);

    UpdateDirectionVectors();

    glm::mat4 worldTransformation = this->GetWorldTransformationMatrix();
    this->worldPosition = this->GetWorldPosition(worldTransformation);
    this->worldRotation = this->GetWorldRotationEuler(worldTransformation);
    this->worldScale = this->GetWorldScale(worldTransformation);

}

void Transform::ResetModelMatrix()
{
	this->modelMatrix = glm::mat4(1.0f);
}

glm::mat4& Transform::GetModelMatrix()
{
	return this->modelMatrix;
}

void Transform::DisplayComponent()
{
        //Position
        ImGui::PushItemWidth(this->inputBoxLength);
        ImGui::Text("Position");
        ImGui::Text("X:");
        ImGui::SameLine();
        ImGui::InputFloat("##posX", &this->localPosition.x, 0.0f, 0.0f, "%.3f");

        ImGui::SameLine();

        ImGui::Text("Y:");
        ImGui::SameLine();

        ImGui::InputFloat("##posY", &this->localPosition.y, 0.0f, 0.0f, "%.3f");
        ImGui::SameLine();

        ImGui::Text("Z:");
        ImGui::SameLine();
        ImGui::InputFloat("##posZ", &this->localPosition.z, 0.0f, 0.0f, "%.3f");

        //Rotation
        ImGui::Text("Rotation");
        ImGui::Text("X:");
        ImGui::SameLine();

        ImGui::InputFloat("##rotX", &this->localRotation.x, 0.0f, 0.0f, "%.3f");
        ImGui::SameLine();

        ImGui::Text("Y:");
        ImGui::SameLine();
        ImGui::InputFloat("##rotY", &this->localRotation.y, 0.0f, 0.0f, "%.3f");
        ImGui::SameLine();

        ImGui::Text("Z:");
        ImGui::SameLine();
        ImGui::InputFloat("##rotZ", &this->localRotation.z, 0.0f, 0.0f, "%.3f");

        //Scale
        ImGui::Text("Scale");
        ImGui::Text("X:");
        ImGui::SameLine();
        ImGui::InputFloat("##scaleX", &this->localScale.x, 0.0f, 0.0f, "%.3f");
        ImGui::SameLine();

        ImGui::Text("Y:");
        ImGui::SameLine();
        ImGui::InputFloat("##scaleY", &this->localScale.y, 0.0f, 0.0f, "%.3f");
        ImGui::SameLine();

        ImGui::Text("Z:");
        ImGui::SameLine();
        ImGui::InputFloat("##scaleZ", &this->localScale.z, 0.0f, 0.0f, "%.3f");
        ImGui::PopItemWidth();
    
}


void Transform::UpdateDirectionVectors()
{
        glm::mat4 rotationYaw = glm::rotate(glm::mat4(1.0f), glm::radians(this->localRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotationPitch = glm::rotate(glm::mat4(1.0f), glm::radians(this->localRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotationRoll = glm::rotate(glm::mat4(1.0f), glm::radians(this->localRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));


        glm::mat4 rotationMatrix = rotationYaw * rotationPitch * rotationRoll;


        this->forward = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
        this->right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
        this->up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
}


Transform* Transform::GetRoot()
{
    Transform* root = nullptr;
    this->GetRootHelper(this, root);
    std::cout << root->GetGameObject()->GetName() << std::endl;
    return root;
}

void Transform::GetRootHelper(Transform* objToCheck, Transform*& root)
{
    if (objToCheck->GetGameObject()->GetParent() == nullptr)
    {
        root = objToCheck;
        return;
    }
    GetRootHelper(objToCheck->GetGameObject()->GetComponent<Transform>(), root);
}



glm::mat4 Transform::GetWorldTransformHelper(Transform* obj)
{
    if (obj->GetGameObject()->GetParent() == nullptr)
    {
        return obj->GetModelMatrix();
    }
    else
    {
        Transform* parentTransform = obj->GetGameObject()->GetParent()->GetComponent<Transform>();
        glm::mat4 parentWorldTransform = GetWorldTransformHelper(parentTransform);
        glm::mat4 localTransform = obj->GetModelMatrix();

        return parentWorldTransform * localTransform;
    }
}

glm::mat4 Transform::GetWorldTransformationMatrix()
{
    return GetWorldTransformHelper(this);
}


glm::vec3 Transform::GetWorldPosition(const glm::mat4& transform)
{
    return glm::vec3(transform[3]);
}

glm::vec3 Transform::GetWorldScale(const glm::mat4& transform)
{
    float scaleX = glm::length(glm::vec3(transform[0]));
    float scaleY = glm::length(glm::vec3(transform[1]));
    float scaleZ = glm::length(glm::vec3(transform[2]));

    return glm::vec3(scaleX, scaleY, scaleZ);
}

glm::vec3 Transform::GetWorldRotationEuler(const glm::mat4& transform)
{
    glm::quat rotationQuat = this->GetWorldRotationQuaternion(transform);

    glm::vec3 eulerAngles = glm::eulerAngles(rotationQuat);

    return glm::degrees(eulerAngles);

}

glm::quat Transform::GetWorldRotationQuaternion(const glm::mat4& transform)
{

    glm::mat3 rotationMatrix = glm::mat3(transform);
    glm::vec3 scale = this->GetWorldScale(transform);

    rotationMatrix[0] /= scale.x;
    rotationMatrix[1] /= scale.y;
    rotationMatrix[2] /= scale.z;

    return glm::quat_cast(rotationMatrix);
}

