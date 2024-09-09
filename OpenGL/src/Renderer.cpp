#include "ErrorHandling.h"
#include "Renderer.h"
#include <iostream>


void Renderer::Draw(GameObject& object, const Shader& shader) const
{
    Shape* shape = object.GetComponent<Shape>();
    if (shape == nullptr) return;
    shape->BindBuffers();
    glDrawElements(GL_TRIANGLES, shape->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawWireframe(GameObject& object, const Shader& shader) const
{
    //TODO BELOW
    Shape* shape = object.GetComponent<Shape>();
    if (shape == nullptr) return;
    shape->BindBuffers();
    glDrawElements(GL_TRIANGLES, shape->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
    glClearColor(this->clearColor[0], this->clearColor[1], this->clearColor[2], this->clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}
