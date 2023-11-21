//
//  VertexArray.cpp
//  OpenGl
//
#include "VertexArray.hpp"

VertexArray::VertexArray(){
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& myVBO, const VertexLayout& layout){
    Bind();
    myVBO.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i=0; i < elements.size(); i++){
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
        offset += element.count * VElement::GetSizeOfType(element.type);
    }
    
        
}   

void VertexArray::Bind() const{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const{
    glBindVertexArray(0);
}