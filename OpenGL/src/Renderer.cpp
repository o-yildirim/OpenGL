#include "Renderer.h"

#include <iostream>


void Renderer::RenderScene(Scene& scene, Shader& shader, Camera* camera) const //TODO, create a material class and attach shaders to that. Not the entire scene.
{
    shader.Bind();

    for (GameObject* object : scene.GetGameObjects())
    {
        RenderObjectRecursively(object, shader, camera);
    }
}


void Renderer::RenderObjectRecursively(GameObject* object, Shader& shader, Camera* camera) const
{
    Transform* transform = object->GetComponent<Transform>();
    transform->Update();
    glm::mat4 modelMatrix = transform->GetWorldModelMatrix();

    glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix() * modelMatrix;
    shader.SetUniformMat4f("u_ModelViewProjection", mvp);
    Draw(*object, shader);

    for (GameObject* child : object->GetChildren())
    {
        RenderObjectRecursively(child, shader, camera);
    }

}


void Renderer::RenderPicking(Shader& shader, Camera* camera) const //TODO, create a material class and attach shaders to that. Not the entire scene.
{
    shader.Bind();

    for (GameObject* pickedObject : Picking::GetSelectedObjects())
    {
        Transform* transform = pickedObject->GetComponent<Transform>();
        glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix() * transform->GetLocalModelMatrix();
        shader.SetUniformMat4f("u_ModelViewProjection", mvp);
        DrawWireframe(*pickedObject, shader);
    }
}



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
