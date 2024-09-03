#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Transform.h"


class Shape: public Component
{
protected:
    float* positions;
    unsigned int* indices; 
    float color[4];
    /*int vertexLength;
    int posLength;
    int colorLength;
    */
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    VertexBufferLayout layout;
    IndexBuffer indexBuffer;

public:
    Shape() = default;
    virtual ~Shape()
    {
        delete[] this->positions;
        delete[] this->indices;
    }
    
    virtual void InitBuffers(){};

    virtual inline void BindBuffers() { this->vertexArray.Bind(); this->vertexBuffer.Bind(); this->indexBuffer.Bind(); }
    virtual inline VertexArray& GetVertexArray() { return this->vertexArray; }
    virtual inline VertexBuffer& GetVertexBuffer() { return this->vertexBuffer; }
    virtual inline IndexBuffer& GetIndexBuffer() { return this->indexBuffer; }
    virtual inline VertexBufferLayout& GetVertexBufferLayout() { return this->layout; }
    //virtual inline int GetVertexLength() { return this->vertexLength; }
    //virtual inline int GetPositionLength() { return this->posLength; }
    //virtual inline int GetColorLength() { return this->colorLength; }
    virtual bool isInside(float x, float y) { return false; }

    //virtual float* GetVertexPositions();

    
};