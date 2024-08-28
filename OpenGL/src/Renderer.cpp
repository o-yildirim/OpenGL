#include "ErrorHandling.h"
#include "Renderer.h"
#include <iostream>


void Renderer::Draw(GameObject& object, const Shader& shader) const
{
    Shape* shape = object.GetComponent<Shape>();
    if (shape == nullptr) return;
    shape->BindBuffers();
    GLCall(glDrawElements(GL_TRIANGLES, shape->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCall(glClearColor(this->clearColor[0], this->clearColor[1], this->clearColor[2], this->clearColor[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
