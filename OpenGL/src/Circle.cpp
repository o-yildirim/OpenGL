#include "Circle.h"
#include <iostream>

Circle::Circle()
{

	this->deltaAngle = 10;
	this->color[0] = 0.0f;
	this->color[1] = 0.5f; 
	this->color[2] = 0.0f; 
	this->color[3] = 1.0f;


	float currentAngle = 0;
	this->radius = 50.0f;

	unsigned int numVertices = this->GetVertexCount(); //+1 is the origin. I will use it in the index buffer.
	unsigned int numIndices = this->GetIndexCount();

	//std::cout << "Num vertices: " << numVertices << ", Num indices: " << numIndices << std::endl;

	this->positions = new float[numVertices];
	this->indices = new unsigned int[numIndices];

	this->positions[0] = 0.0f;
	this->positions[1] = 0.0f;
	this->positions[2] = this->color[0];//r
	this->positions[3] = this->color[1];//g
	this->positions[4] = this->color[2];//b
	this->positions[5] = this->color[3];//a


	//std::cout << "x: " << this->positions[0] << ", y:" << this->positions[1] << std::endl;
	for(int i = 6; i<numVertices;i+=6)
	{
		float currentAngleInRadians = glm::radians(currentAngle);
		float x = this->radius * glm::cos(currentAngleInRadians);
		float y = this->radius * glm::sin(currentAngleInRadians);
		this->positions[i] = x;
		this->positions[i + 1] = y;
		
		this->positions[i + 2] = this->color[0];//r
		this->positions[i + 3] = this->color[1];//g
		this->positions[i + 4] = this->color[2];//b
		this->positions[i + 5] = this->color[3];//a

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

	this->InitBuffers();

}


void Circle::InitBuffers()
{
	this->vertexBuffer.AddData(this->positions, this->GetVertexCount() * sizeof(float));
	this->layout.Push<float>(2);
	//this->posLength = 2;

	this->layout.Push<float>(4);
	//this->colorLength = 4;

	this->vertexArray.AddBuffer(this->vertexBuffer, layout);
	this->indexBuffer.AddData(this->indices, this->GetIndexCount());
	//this->vertexLength = 6;
}

unsigned int Circle::GetIndexCount()
{
	return 3 * (360.0f / this->deltaAngle);
}

unsigned int Circle::GetVertexCount()
{
	return 6 * ((360.0f / this->deltaAngle) + 1); //The reason we say 6 is 2 for x,y and 4 for color.
}

bool Circle::isInside(float x, float y)
{
	Transform* transform = this->GetParent()->GetComponent<Transform>();
	float distance = glm::distance(glm::vec2(x,y), glm::vec2(transform->position.x,transform->position.y));
	std::cout << distance << std::endl;
	if (distance <= this->radius)
	{
		std::cout << "Inside circle." << std::endl;
		return true;
	}
	return false;
}
