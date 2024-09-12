#include "Renderer.h"

#include <iostream>


void Renderer::Draw(GameObject& object, const Shader& shader) const
{
    //shader.Bind();
    Shape* shape = object.GetComponent<Shape>();
    if (shape == nullptr) return;
    shape->BindBuffers();
    glDrawElements(GL_TRIANGLES, shape->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
    shape->UnbindBuffers();
}

void Renderer::DrawWireframe(GameObject& object, const Shader& shader) const
{
    //shader.Bind();
    Shape* shape = object.GetComponent<Shape>();
    if (shape == nullptr) return;
    shape->BindBuffers();
    glLineWidth(3.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_LINE_LOOP, shape->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shape->UnbindBuffers();

}

void Renderer::Clear() const
{
    glClearColor(this->clearColor[0], this->clearColor[1], this->clearColor[2], this->clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}
