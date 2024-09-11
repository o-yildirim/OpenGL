#include "Rectangle.h"

Rectangle::Rectangle()
{
    this->_className = "Rectangle";

    this->xLength = 100.0f;
    this->yLength = 100.0f;

    this->positions = new float[24];
    this->indices = new unsigned int[6];
    this->color[0] = 1.0f;//r
    this->color[1] = 1.0f;//g
    this->color[2] = 1.0f;//b
    this->color[3] = 1.0f;//a


    this->SetPositions();
    this->SetIndices();
    this->SetColor();

    this->InitBuffers();
}

void Rectangle::InitBuffers()
{
    this->vertexBuffer.AddData(this->positions, 4 * 6 * sizeof(float));
    this->layout.Push<float>(2);
    //this->posLength = 2;

    this->layout.Push<float>(4);
    //this->colorLength = 4;

    this->vertexArray.AddBuffer(this->vertexBuffer, layout);
    this->indexBuffer.AddData(this->indices, 6);
    //this->vertexLength = 6;

}

bool Rectangle::isInside(float x, float y)
{

    
    Transform* transform = this->GetParent()->GetComponent<Transform>();
  

    float halfLengthX = (xLength * transform->scale.x) / 2.0f;
    float halfLengthY = (yLength * transform->scale.y) / 2.0f;


    float relX = x - transform->position.x;
    float relY = y - transform->position.y;



    float angle = glm::radians(transform->rotation.z);


    float rotatedX = relX * glm::cos(angle) + relY * glm::sin(angle);
    float rotatedY = -relX * glm::sin(angle) + relY * glm::cos(angle);


    if (rotatedX >= -halfLengthX && rotatedX <= halfLengthX &&
        rotatedY >= -halfLengthY && rotatedY <= halfLengthY)
    {
        std::cout << "Inside square." << std::endl;
        return true;
    }
    return false;




}





void Rectangle::SetPositions()
{
    this->positions[0] = -this->xLength / 2.0f;//x
    this->positions[1] = -this->yLength / 2.0f;//y

    this->positions[6] = this->xLength / 2.0f; //x
    this->positions[7] = -this->yLength / 2.0f; //y

    this->positions[12] = this->xLength / 2.0f; //x
    this->positions[13] = this->yLength / 2.0f;//y

    this->positions[18] = -this->xLength / 2.0f; //x
    this->positions[19] = this->yLength / 2.0f; //y
}

void Rectangle::SetIndices()
{
    this->indices[0] = 0;
    this->indices[1] = 1;
    this->indices[2] = 2;
    this->indices[3] = 2;
    this->indices[4] = 3;
    this->indices[5] = 0;
}


size_t Rectangle::GetVertexCount()
{
    return 24; //6 floats per vertex (2 pos, 4 colors) and we have 4 vertices.
}




