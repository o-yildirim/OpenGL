#include "Rectangle.h"

Rectangle::Rectangle()
{
    this->positions = new float[8];
    this->indices = new unsigned int[6];

    this->positions[0] = -50.0f;
    this->positions[1] = -50.0f;
    this->positions[2] = 50.0f;
    this->positions[3] = -50.0f;
    this->positions[4] = 50.0f;
    this->positions[5] = 50.0f;
    this->positions[6] = -50.0f;
    this->positions[7] = 50.0f;

    this->indices[0] = 0;
    this->indices[1] = 1;
    this->indices[2] = 2;
    this->indices[3] = 2;
    this->indices[4] = 3;
    this->indices[5] = 0;


    this->InitBuffers();
}

void Rectangle::InitBuffers()
{

    this->vertexBuffer.AddData(this->positions, 4 * 2 * sizeof(float));
    this->layout.Push<float>(2);
    this->vertexArray.AddBuffer(this->vertexBuffer, layout);
    this->indexBuffer.AddData(this->indices, 6);
}


