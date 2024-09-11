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
    virtual inline void UnbindBuffers() { this->vertexArray.Unbind(); this->vertexBuffer.Unbind(); this->indexBuffer.Unbind(); }
    virtual inline VertexArray& GetVertexArray() { return this->vertexArray; }
    virtual inline VertexBuffer& GetVertexBuffer() { return this->vertexBuffer; }
    virtual inline IndexBuffer& GetIndexBuffer() { return this->indexBuffer; }
    virtual inline VertexBufferLayout& GetVertexBufferLayout() { return this->layout; }
    virtual void SetColor() 
    {
            int colorIndex = 0;
            int numVertices = this->GetVertexCount();
            for (int i = 2; i < numVertices; i += 6)
            {
                this->positions[i] = this->color[colorIndex++];//r
                this->positions[i + 1] = this->color[colorIndex++];//g
                this->positions[i + 2] = this->color[colorIndex++];//b
                this->positions[i + 3] = this->color[colorIndex++];//a
                colorIndex = 0;
            }      
            this->vertexBuffer.UpdateData(this->positions, this->GetVertexCount() * sizeof(float));
    }

    virtual void DisplayComponent()
    {
        if (ImGui::CollapsingHeader(this->_className, ImGuiTreeNodeFlags_DefaultOpen))//If not minimized.
        {
            if (ImGui::ColorEdit4("Color", this->color)) //If color is changed, render with new color.
            {
                std::cout << this->color[0] << ", " << this->color[1] << ", " << this->color[2] << ", " << this->color[3] << std::endl;
                this->SetColor();
            }

        }
    }

    virtual void SetIndices() { }
    virtual void SetPositions(){ }
    virtual size_t GetVertexCount() { return 0; }
   

    //virtual inline int GetVertexLength() { return this->vertexLength; }
    //virtual inline int GetPositionLength() { return this->posLength; }
    //virtual inline int GetColorLength() { return this->colorLength; }
    virtual bool isInside(float x, float y) { return false; }


    //virtual float* GetVertexPositions();

    
};