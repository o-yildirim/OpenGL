#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GameObject.h"
#include "Shape.h"

class Renderer
{
private:
    float clearColor[4] = { 0.0f, 0.1f, 0.3f, 1.0f };
public:
    void Draw(GameObject& object, const Shader& shader) const;
    void DrawWireframe(GameObject& object, const Shader& shader) const;
    void Clear() const;
};