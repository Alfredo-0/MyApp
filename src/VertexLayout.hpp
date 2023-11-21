//
//  VertexLayout.hpp
//  OpenGl
//
#pragma once
#include <vector>
#include <GL/glew.h>

struct VElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch (type){
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_BYTE:  return 1;
            case GL_UNSIGNED_INT:   return 4;
        }
        return 0;
    }
};

class VertexLayout {
private:
    std::vector<VElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexLayout()
        : m_Stride(0){ }
    //~VertexLayout();

    template<typename T>
    inline void Push(unsigned int count){
        //static_assert(false);
    }

    inline const std::vector<VElement> GetElements() const {return m_Elements;}
    inline unsigned int GetStride() const {return m_Stride;}
};

template<>
inline void VertexLayout::Push<float>(unsigned int count){
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += VElement::GetSizeOfType(GL_FLOAT)*count;
}

template<>
inline void VertexLayout::Push<unsigned int>(unsigned int count){
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += VElement::GetSizeOfType(GL_UNSIGNED_INT)*count;
}

template<>
inline void VertexLayout::Push<char>(unsigned int count){
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += VElement::GetSizeOfType(GL_UNSIGNED_BYTE)*count;
}
