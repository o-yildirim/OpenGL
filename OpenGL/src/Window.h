#pragma once
#include "glm/glm.hpp"

class Window {
private:
    static const int width;
    static const int height;
    static const glm::vec3 center;

public:
    inline static int GetWidth()  { return width; }
    inline static int GetHeight()  { return height; }
    inline static glm::vec3 GetCenter() { return center; }

};