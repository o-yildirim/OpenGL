#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GameObject.h"
#include "Shapes.h"
#include "Scene.h"
#include "Camera.h"
#include "Picking.h"

class Scene;

class Renderer
{
private:
    float clearColor[4] = { 0.0f, 0.1f, 0.3f, 1.0f };
    void RenderObjectRecursively(GameObject* object, Shader& shader, Camera* camera) const;
public:
    void Draw(GameObject& object, const Shader& shader) const;
    void DrawWireframe(GameObject& object, const Shader& shader) const;
    void RenderScene(Scene& scene, Shader& shader, Camera* camera) const;
    void RenderPicking(Shader& shader, Camera* camera) const;
    void Clear() const;
};