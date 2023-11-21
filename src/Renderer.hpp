//
//  Renderer.hpp
//  OpenGl
//
#pragma once

#include <iostream>
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

#define ASSERT(x) if (!(x)) __builtin_trap();
#define GLCall(x) GLCLearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer{
public:
    void Draw(const VertexArray& VAO, const IndexBuffer& VBO, const Shader& Shader) const;
    void Clear() const;
};