//
//  Shader.cpp
//  OpenGl_1
//

#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>

Shader::Shader(const std::string& fileVertex, const std::string& fileFragment)
    : m_FileVertex(fileVertex), m_FileFragment(fileFragment), m_RendererID(0){
    std::string vertexShader = readFileToString(RESOURCES_PATH + m_FileVertex);
    std::string fragmentShader = readFileToString(RESOURCES_PATH + m_FileFragment);

    m_RendererID = Shader::CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader(){
    glDeleteShader(m_RendererID);
}

std::string Shader::readFileToString(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    std::stringstream stream;
    if (!file.is_open()) {
        std::cerr << "Error opening the file: " << filepath << std::endl;
        return "";
    }

    while(getline(file, line)){
        stream << line << '\n';
    }

    file.close();
    return stream.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,  1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght*sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout<<"Failed to Compile "<<(type == GL_VERTEX_SHADER ? "vertex": "fragment") << "shader!" << '\n';
        std::cout<<message<<'\n';
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program  = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

void Shader::Bind() const{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3){ 
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform2f(const std:: string& name, float v0, float v1){
    glUniform2f(GetUniformLocation(name), v0, v1);

}


unsigned int Shader::GetUniformLocation(const std::string& name){
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout<< "Warning: uniform "<<name<<" does not exist\n"; 
    m_UniformLocationCache[name] = location;
    return (unsigned int)location;
}
