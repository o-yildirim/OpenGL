#pragma once
#include "Component.h"
#include "glm/glm.hpp"

class Rigidbody: public Component
{
private:
	glm::vec3 position;
	glm::vec3 velocity;
	float mass;
public:
	void Update();
};