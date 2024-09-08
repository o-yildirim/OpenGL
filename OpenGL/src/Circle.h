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
	void SetPositions() override;
	void SetIndices() override;
	size_t GetVertexCount() override;
	size_t GetIndexCount();
};