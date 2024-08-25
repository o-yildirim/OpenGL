#pragma once
#include "Shape.h"
#include "glm/glm.hpp"
#include <iostream>

class Rectangle:public Shape
{
public:
	Rectangle();

	void InitBuffers() override;
};