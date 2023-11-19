#pragma once

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#endif /* VertexBuffer_hpp */

class VertexBuffer {
private:
    unsigned int m_RendererID;
    
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    
    void Bind() const;
    void Unbind() const;
};
