#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GameObject.h"
#include "Shape.h"

class Renderer
{
public:
    void Draw(GameObject& object, const Shader& shader) const;
    void Clear() const;
};