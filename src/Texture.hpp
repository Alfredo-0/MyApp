#pragma once

#include "Renderer.hpp"
#include <string>


class Texture{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Heigth, m_BPP;
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; };
    inline int GetHeigth() const { return m_Heigth; };
};