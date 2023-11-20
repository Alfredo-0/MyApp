//OpenGL
//Created by Alfredo

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"


#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

const double pi = std::acos(-1);

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static std::string readFileToString(const std::string& filepath) {
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

static unsigned int CompileShader(unsigned int type, const std::string& source){
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


static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
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


int main (void){
    glfwInit();
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, World!", NULL, NULL);
    
    if (window == NULL){
        std::cout<<"Failed to create GLFW window!\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glewInit();
    
    float points[] = {
         0.5,  0.5, //0
        -0.1,  0.5, //1
        -0.5, -0.5, //2
         0.5, -0.6, //3
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    
    VertexBuffer myVBO(points, sizeof(points));
    unsigned int myVAO;
    
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)0);
    
    IndexBuffer myIB(indices, 6);

    std::string vertexShader = readFileToString(RESOURCES_PATH "shader/vertex.shader");
    std::string fragmentShader = readFileToString(RESOURCES_PATH "shader/fragment.shader");

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);
    
    int location = glGetUniformLocation(shader, "u_Color");\
    glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f);
    
    float r = 0.;
    float increment = .005f;

    while ( !glfwWindowShouldClose(window) ) {

        glClear(GL_COLOR_BUFFER_BIT);
        glUniform4f(location, r, r/2, .3f, 1.f);

        glBindVertexArray(myVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if( r > 1.0f)
            increment = -0.005f;
        else if ( r < 0.0f )
            increment = 0.005f;
        r += increment;
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteProgram(shader);

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}