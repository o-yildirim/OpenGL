#include "Rectangle.h"

Rectangle::Rectangle()
{
    this->positions = new float[24];
    this->indices = new unsigned int[6];
    this->color[0] = 1.0f;//r
    this->color[1] = 1.0f;//g
    this->color[2] = 1.0f;//b
    this->color[3] = 1.0f;//a

    this->positions[0] = -50.0f;//x
    this->positions[1] = -50.0f;//y
    this->positions[2] = this->color[0]; //r
    this->positions[3] = this->color[1]; //g
    this->positions[4] = this->color[2]; //b
    this->positions[5] = this->color[3]; //a

    this->positions[6] = 50.0f; //x
    this->positions[7] = -50.0f; //y
    this->positions[8] = this->color[0]; //r
    this->positions[9] = this->color[1]; //g
    this->positions[10] = this->color[2]; //b
    this->positions[11] = this->color[3]; //a


    this->positions[12] = 50.0f; //x
    this->positions[13] = 50.0f;//y
    this->positions[14] = this->color[0]; //r
    this->positions[15] = this->color[1]; //g
    this->positions[16] = this->color[2]; //b
    this->positions[17] = this->color[3]; //a


    this->positions[18] = -50.0f; //x
    this->positions[19] = 50.0f; //y
    this->positions[20] = this->color[0]; //r
    this->positions[21] = this->color[1]; //g
    this->positions[22] = this->color[2]; //b
    this->positions[23] = this->color[3]; //a

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
    this->vertexBuffer.AddData(this->positions, 4 * 6 * sizeof(float));
    this->layout.Push<float>(2);
    this->layout.Push<float>(4);
    this->vertexArray.AddBuffer(this->vertexBuffer, layout);
    this->indexBuffer.AddData(this->indices, 6);
}


