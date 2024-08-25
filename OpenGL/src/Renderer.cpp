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
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
