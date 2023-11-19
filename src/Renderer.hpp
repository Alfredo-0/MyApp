#pragma once
#ifndef Renderer_hpp
#define Renderer_hpp

#include <GL/glew.h>
#include <iostream>

#endif /* Renderer_hpp */

#define ASSERT(x) if (!(x)) __builtin_trap();
#define GLCall(x) GLCLearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
