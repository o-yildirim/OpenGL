#include "Circle.h"
#include <iostream>

Circle::Circle()
{

	this->_className = "Circle";

	this->deltaAngle = 10;
	this->color[0] = 0.0f;
	this->color[1] = 0.5f; 
	this->color[2] = 0.0f; 
	this->color[3] = 1.0f;


	
	this->radius = 50.0f;

	unsigned int numVertices = this->GetVertexCount(); //+1 is the origin. I will use it in the index buffer.
	unsigned int numIndices = this->GetIndexCount();

	//std::cout << "Num vertices: " << numVertices << ", Num indices: " << numIndices << std::endl;

	this->positions = new float[numVertices];
	this->indices = new unsigned int[numIndices];

	this->SetPositions();
	this->SetIndices();
	this->SetColor();


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

size_t Circle::GetIndexCount()
{
	return 3 * (360.0f / this->deltaAngle);
}

size_t Circle::GetVertexCount()
{
	return 6 * ((360.0f / this->deltaAngle) + 1); //The reason we say 6 is 2 for x,y and 4 for color.
}

bool Circle::isInside(float x, float y)
{
	Transform* transform = this->GetParent()->GetComponent<Transform>();


	float halfLengthX = (this->radius * transform->scale.x);
	float halfLengthY = (this->radius * transform->scale.y);


	float relX = x - transform->position.x;
	float relY = y - transform->position.y;



	float angle = glm::radians(transform->rotation.z);


	float rotatedX = relX * glm::cos(angle) + relY * glm::sin(angle);
	float rotatedY = -relX * glm::sin(angle) + relY * glm::cos(angle);


	if (rotatedX >= -halfLengthX && rotatedX <= halfLengthX &&
		rotatedY >= -halfLengthY && rotatedY <= halfLengthY)
	{
		std::cout << "Inside circle." << std::endl;
		return true;
	}
	return false;
}

void Circle::SetIndices()
{
	unsigned int counter = 1;
	int numIndices = this->GetIndexCount();
	for (int i = 0; i < numIndices; i += 3)
	{
		this->indices[i] = 0;
		this->indices[i + 1] = counter;
		this->indices[i + 2] = counter + 1;
		counter++;
	}
	this->indices[numIndices - 1] = 1;
}

void Circle::SetPositions()
{
	this->positions[0] = 0.0f;
	this->positions[1] = 0.0f;

	float currentAngle = 0;
	int numVertices = this->GetVertexCount();
	//std::cout << "x: " << this->positions[0] << ", y:" << this->positions[1] << std::endl;
	for (int i = 6; i < numVertices; i += 6)
	{
		float currentAngleInRadians = glm::radians(currentAngle);
		float x = this->radius * glm::cos(currentAngleInRadians);
		float y = this->radius * glm::sin(currentAngleInRadians);
		this->positions[i] = x;
		this->positions[i + 1] = y;


		currentAngle += deltaAngle;

		//std::cout << "x: " << this->positions[i] << ", y:" << this->positions[i + 1] << std::endl;
	}

}