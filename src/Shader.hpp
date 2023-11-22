//
//  Shader.hpp
//  OpenGl
//
#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

class Shader{
private:
    unsigned int m_RendererID;
    std::string m_FileVertex;
    std::string m_FileFragment;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& fileVertex, const std::string& fileFragment);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    //Set uniforms
    void SetUniform4f(const std:: string& name, float v0, float v1, float v2, float v3);
    void SetUniform2f(const std:: string& name, float v0, float v1);
    void SetUniform1f(const std:: string& name, float v0);

private:
    unsigned int GetUniformLocation(const std::string& name);
    std::string readFileToString(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};
