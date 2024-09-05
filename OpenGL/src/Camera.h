#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include "Window.h"
#include"glm/gtc/matrix_transform.hpp"

class Camera : public Component
{
private:
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
public:
	Camera();

	inline glm::mat4& GetProjectionMatrix() { return this->_projectionMatrix; }
	inline glm::mat4& GetViewMatrix() { return this->_viewMatrix; }
	inline void SetProjectionMatrix(glm::mat4 proj) { this->_projectionMatrix = proj; }
	inline void SetViewMatrix(glm::mat4 view) { this->_viewMatrix = view; }
	glm::vec3 ConvertScreenToWorld(glm::vec3 pos);
};