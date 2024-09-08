#pragma once
#include "Shape.h"
#include "glm/glm.hpp"
#include <iostream>

class Rectangle:public Shape
{
private:
	float xLength, yLength;
public:
	Rectangle();
	void InitBuffers() override;
	bool isInside(float x, float y) override;
	void SetIndices() override;
	void SetPositions() override;
	size_t GetVertexCount() override;
};