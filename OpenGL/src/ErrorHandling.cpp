#include <iostream>
#include <GL/glew.h>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR); //Clears errors.
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}