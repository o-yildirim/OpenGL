#pragma once
#include "glm/glm.hpp"

class Window {
private:
    static int _width;
    static int _height;
    static glm::vec3 _center;

    static int _usableWidth;
    static int _usableHeight;
    static glm::vec3 _usableCenter;


public:
    static void Init();
    static void UpdateWindowAttributes();

    //Part below returns values according to the window.
    inline static int GetWidth()  { return _width; }
    inline static int GetHeight()  { return _height; }
    inline static glm::vec3 GetCenter() { return _center; }

    //The part below returns the values after the sizes of the UI elements are substracted. E.g. returns the part that belongs to OpenGL.
    inline static int GetAvailableWidth() { return _usableWidth; }
    inline static int GetAvailableHeight() { return _usableHeight; }
    inline static glm::vec3 GetAvailableCenter() { return _usableCenter; }

};