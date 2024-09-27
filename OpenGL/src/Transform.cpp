#include "Transform.h"
#include "Window.h"


Transform::Transform()
{
    this->_className = "Transform";
	this->localModelMatrix = glm::mat4(1.0f);
    isDirty = true;

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
	this->localPosition = toPosition;
    this->MarkDirty();
}

void Transform::Rotate(float angle,glm::vec3 axisToRotateAround)
{
	for (int i = 0; i < 3; i++)
	{
		if (axisToRotateAround[i] == 1)
		{
			this->localRotation[i] += angle;
			break;
		}
	}
    this->MarkDirty();
}

void Transform::Scale(glm::vec3 newScale)
{
	this->localScale = newScale;
    this->MarkDirty();
}

void Transform::Update()
{
    if (this->disabled && this->GetGameObject()->GetDisabled()) return;

    if (this->isDirty)
    {
        this->ResetModelMatrix();

        
        this->localModelMatrix = glm::translate(this->localModelMatrix, this->localPosition);
        this->localModelMatrix = glm::rotate(this->localModelMatrix, glm::radians(this->localRotation.x), glm::vec3(1, 0, 0));
        this->localModelMatrix = glm::rotate(this->localModelMatrix, glm::radians(this->localRotation.y), glm::vec3(0, 1, 0));
        this->localModelMatrix = glm::rotate(this->localModelMatrix, glm::radians(this->localRotation.z), glm::vec3(0, 0, 1));
        this->localModelMatrix = glm::scale(this->localModelMatrix, this->localScale);

        UpdateDirectionVectors();
        
        this->worldModelMatrix = this->ComputeWorldTransformationMatrix();
        this->worldPosition = this->GetWorldPosition();
        this->worldRotation = this->GetWorldRotationEuler();
        this->worldScale = this->GetWorldScale();
        
        this->isDirty = false;
        
    }

}

void Transform::ResetModelMatrix()
{
	this->localModelMatrix = glm::mat4(1.0f);
}

glm::mat4& Transform::GetWorldModelMatrix()
{
	return this->worldModelMatrix;
}

glm::mat4& Transform::GetLocalModelMatrix()
{
    return this->localModelMatrix;
}

void Transform::DisplayComponent()
{
        bool changed = false;

        //Position
        ImGui::PushItemWidth(this->inputBoxLength);
        ImGui::Text("Position");
        ImGui::Text("X:");
        ImGui::SameLine();
        changed |= ImGui::InputFloat("##posX", &this->localPosition.x, 0.0f, 0.0f, "%.3f");

        ImGui::SameLine();

        ImGui::Text("Y:");
        ImGui::SameLine();
        changed |= ImGui::InputFloat("##posY", &this->localPosition.y, 0.0f, 0.0f, "%.3f");
        ImGui::SameLine();

        ImGui::Text("Z:");
        ImGui::SameLine();
        changed |= ImGui::InputFloat("##posZ", &this->localPosition.z, 0.0f, 0.0f, "%.3f");

        //Rotation
        ImGui::Text("Rotation");
        ImGui::Text("X:");
        ImGui::SameLine();
        changed |= ImGui::InputFloat("##rotX", &this->localRotation.x, 0.0f, 0.0f, "%.3f");

        ImGui::SameLine();

        ImGui::Text("Y:");
        ImGui::SameLine();
        changed |= ImGui::InputFloat("##rotY", &this->localRotation.y, 0.0f, 0.0f, "%.3f");
        ImGui::SameLine();

        ImGui::Text("Z:");
        ImGui::SameLine();
        changed |= ImGui::InputFloat("##rotZ", &this->localRotation.z, 0.0f, 0.0f, "%.3f");

        //Scale
        ImGui::Text("Scale");
        ImGui::Text("X:");
        ImGui::SameLine();
        changed |= ImGui::InputFloat("##scaleX", &this->localScale.x, 0.0f, 0.0f, "%.3f");
        ImGui::SameLine();

        ImGui::Text("Y:");
        ImGui::SameLine();
        changed |= ImGui::InputFloat("##scaleY", &this->localScale.y, 0.0f, 0.0f, "%.3f");
        ImGui::SameLine();

        ImGui::Text("Z:");
        ImGui::SameLine();
        changed |= ImGui::InputFloat("##scaleZ", &this->localScale.z, 0.0f, 0.0f, "%.3f");
        ImGui::PopItemWidth();   

        if (changed)
        {
            this->MarkDirty();
        }
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
        return obj->GetLocalModelMatrix();
    }
    else
    {
        Transform* parentTransform = obj->GetGameObject()->GetParent()->GetComponent<Transform>();
        glm::mat4 parentWorldTransform = GetWorldTransformHelper(parentTransform);
        glm::mat4 localTransform = obj->GetLocalModelMatrix();

        return parentWorldTransform * localTransform;
    }
}

glm::mat4 Transform::ComputeWorldTransformationMatrix()
{
    return GetWorldTransformHelper(this);
}

glm::vec3 Transform::GetLocalPosition()
{
    return glm::vec3(this->localModelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

glm::vec3 Transform::GetWorldPosition()
{
    return glm::vec3(this->worldModelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

glm::vec3 Transform::GetWorldScale()
{
    float scaleX = glm::length(glm::vec3(this->worldModelMatrix[0]));
    float scaleY = glm::length(glm::vec3(this->worldModelMatrix[1]));
    float scaleZ = glm::length(glm::vec3(this->worldModelMatrix[2]));

    return glm::vec3(scaleX, scaleY, scaleZ);
}

glm::vec3 Transform::GetWorldRotationEuler()
{
    glm::quat rotationQuat = this->GetWorldRotationQuaternion();
    glm::vec3 eulerAngles = glm::eulerAngles(rotationQuat);
    return glm::degrees(eulerAngles);
}

glm::quat Transform::GetWorldRotationQuaternion()
{
    glm::mat3 rotationMatrix = glm::mat3(this->worldModelMatrix);
    glm::vec3 scale = this->GetWorldScale();

    rotationMatrix[0] /= scale.x;
    rotationMatrix[1] /= scale.y;
    rotationMatrix[2] /= scale.z;

    return glm::quat_cast(rotationMatrix);
}

void Transform::MarkDirty()
{
    this->isDirty = true;

    for (GameObject* child : this->GetGameObject()->GetChildren())
    {
        Transform* childTransform = child->GetComponent<Transform>();
        childTransform->MarkDirty(); 
    }
}


glm::vec3 Transform::WorldToLocalPosition(const glm::vec3& worldPos) const
{
    GameObject* parentObj = this->GetGameObject()->GetParent();
    if (parentObj != nullptr)
    {
        glm::mat4 inverseParentWorldMatrix = glm::inverse(parentObj->GetComponent<Transform>()->GetWorldModelMatrix());
        return glm::vec3(inverseParentWorldMatrix * glm::vec4(worldPos, 1.0f));
    }

    return worldPos;
}

glm::vec3 Transform::WorldToLocalRotation(const glm::vec3& eulerRot) const
{
    GameObject* parentObj = this->GetGameObject()->GetParent();
    if (parentObj != nullptr)
    {
        glm::quat worldRotationQuat = glm::quat(glm::radians(eulerRot));
        glm::quat parentWorldRotation = parentObj->GetComponent<Transform>()->GetWorldRotationQuaternion();
        glm::quat localRotationQuat = glm::inverse(parentWorldRotation) * worldRotationQuat;
        return glm::degrees(glm::eulerAngles(localRotationQuat));
    }

    return eulerRot;
}

glm::vec3 Transform::WorldToLocalScale(const glm::vec3& worldScale) const
{
    GameObject* parentObj = this->GetGameObject()->GetParent();
    if (parentObj != nullptr)
    {
        glm::vec3 parentWorldScale = parentObj->GetComponent<Transform>()->GetWorldScale();
        return worldScale / parentWorldScale;
    }

    return worldScale; 
}

void Transform::SetLocalFromWorldMatrix(const glm::mat4& localMatrix)
{
    this->localPosition = localMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    this->localScale[0] = glm::length(glm::vec3(localMatrix[0]));
    this->localScale[1] = glm::length(glm::vec3(localMatrix[1]));
    this->localScale[2] = glm::length(glm::vec3(localMatrix[2]));

    glm::mat3 rotationMatrix = glm::mat3(localMatrix);
    glm::vec3 scale = this->localScale;

    rotationMatrix[0] /= scale.x;
    rotationMatrix[1] /= scale.y;
    rotationMatrix[2] /= scale.z;

    glm::quat localRotQuat = glm::quat_cast(rotationMatrix);
    this->localRotation = glm::eulerAngles(localRotQuat);
}