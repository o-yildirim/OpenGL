#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	float deltaAngle;
	float radius;
public:
	Circle();

	void InitBuffers() override;
	bool isInside(float x, float y) override;
	unsigned int GetVertexCount();
	unsigned int GetIndexCount();
};