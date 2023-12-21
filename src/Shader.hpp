//
//  Shader.hpp
//  OpenGl
//
#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <GL/glew.h>



class Shader{
private:
    unsigned int m_RendererID;
    std::string m_FileVertex;
    std::string m_FileFragment;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& fileVertex, const std::string& fileFragment)
        : m_FileVertex(fileVertex), m_FileFragment(fileFragment), m_RendererID(0){
        std::string vertexShader = readFileToString(RESOURCES_PATH + m_FileVertex);
        std::string fragmentShader = readFileToString(RESOURCES_PATH + m_FileFragment);

        m_RendererID = Shader::CreateShader(vertexShader, fragmentShader);
    }
    
    ~Shader(){
        glDeleteShader(m_RendererID);
    }

    void Bind() const{
        glUseProgram(m_RendererID);
    }
    void Unbind() const{
        glUseProgram(0);
    }

    //Set uniforms
    void SetUniform4f(const std:: string& name, float v0, float v1, float v2, float v3){
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }
    void SetUniform2f(const std:: string& name, float v0, float v1){
        glUniform2f(GetUniformLocation(name), v0, v1);
    }
    void SetUniform1f(const std:: string& name, float value){
        glUniform1f(GetUniformLocation(name), value);
    }
    void SetUniform1i(const std:: string& name, int value){
        glUniform1i(GetUniformLocation(name), value);
    }

private:
    std::string readFileToString(const std::string& filepath) {
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

    unsigned int GetUniformLocation(const std::string& name){
        if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];

        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
            std::cout<< "Warning: uniform "<<name<<" does not exist\n"; 
        m_UniformLocationCache[name] = location;
        return (unsigned int)location;    
    }
    
    unsigned int CompileShader(unsigned int type, const std::string& source){
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
    
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
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
};
