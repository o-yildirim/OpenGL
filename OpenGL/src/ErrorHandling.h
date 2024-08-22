#pragma once
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)) //# turns the function name into a string.

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);