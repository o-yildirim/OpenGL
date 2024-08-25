#include "Circle.h"
#include <iostream>

Circle::Circle()
{

	this->deltaAngle = 10;

	float currentAngle = 0;
	float radius = 50.0f;

	unsigned int numVertices = this->GetVertexCount(); //+1 is the origin. I will use it in the index buffer.
	unsigned int numIndices = this->GetIndexCount();

	//std::cout << "Num vertices: " << numVertices << ", Num indices: " << numIndices << std::endl;

	this->positions = new float[numVertices];
	this->indices = new unsigned int[numIndices];

	this->positions[0] = 0.0f;
	this->positions[1] = 0.0f;
	
	//std::cout << "x: " << this->positions[0] << ", y:" << this->positions[1] << std::endl;
	for(int i = 2; i<numVertices;i+=2)
	{
		float currentAngleInRadians = glm::radians(currentAngle);
		float x = radius * glm::cos(currentAngleInRadians);
		float y = radius * glm::sin(currentAngleInRadians);
		this->positions[i] = x;
		this->positions[i + 1] = y;

		currentAngle += deltaAngle;

		//std::cout << "x: " << this->positions[i] << ", y:" << this->positions[i + 1] << std::endl;
	}

	unsigned int counter = 1;
	for (int i = 0; i < numIndices; i+=3)
	{
		this->indices[i] = 0;
		this->indices[i + 1] = counter;
		this->indices[i + 2] = counter+1;
		counter++;
	}
	this->indices[numIndices - 1] = 1;

	/*for (int i = 0; i < numIndices; i += 3)
	{
		std::cout << this->indices[i] << "," << this->indices[i + 1] << "," << this->indices[i + 2] << std::endl;
	}*/

	this->InitBuffers();
}


void Circle::InitBuffers()
{
	this->vertexBuffer.AddData(this->positions, this->GetVertexCount() * sizeof(float));
	this->layout.Push<float>(2);
	this->vertexArray.AddBuffer(this->vertexBuffer, layout);
	this->indexBuffer.AddData(this->indices, this->GetIndexCount());
}

unsigned int Circle::GetIndexCount()
{
	return 3 * (360.0f / this->deltaAngle);
}

unsigned int Circle::GetVertexCount()
{
	return 2 * ((360.0f / this->deltaAngle) + 1);
}
