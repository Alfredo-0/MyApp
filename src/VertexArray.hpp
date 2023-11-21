//
//  VertexArray.hpp
//  OpenGl
//
#pragma once

#include "VertexBuffer.hpp"
#include "VertexLayout.hpp"

class VertexArray {
private:
    unsigned int m_RendererID;
    
public:
    VertexArray();
    ~VertexArray();
    
    void AddBuffer(const VertexBuffer& myVBO, const VertexLayout& layout);

    void Bind() const;
    void Unbind() const;
};
