#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	float deltaAngle;
public:
	Circle();

	void InitBuffers() override;
	unsigned int GetVertexCount();
	unsigned int GetIndexCount();
};