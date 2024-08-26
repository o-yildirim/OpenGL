#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"


class Shape: public Component
{
protected:
    float* positions;
    unsigned int* indices; 

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    VertexBufferLayout layout;
    IndexBuffer indexBuffer;

public:
    Shape() = default;
    virtual ~Shape()
    {
        std::cout << "Called destructor" << std::endl;
        delete[] this->positions;
        delete[] this->indices;
    }
    
    virtual void InitBuffers(){};

    virtual inline void BindBuffers() { this->vertexArray.Bind(); this->vertexBuffer.Bind(); this->indexBuffer.Bind(); }
    virtual inline VertexArray& GetVertexArray() { return this->vertexArray; }
    virtual inline VertexBuffer& GetVertexBuffer() { return this->vertexBuffer; }
    virtual inline IndexBuffer& GetIndexBuffer() { return this->indexBuffer; }

    
};