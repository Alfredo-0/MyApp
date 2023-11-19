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

const double pi = std::acos(-1);

void init (void){
    float points[] = {
         0.5,  0.5,
        -0.5, -0.5,
         0.5, -0.5,
        -0.5,  0.5,
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexBuffer myVBO(points, sizeof(points));
    unsigned int myVAO;
    
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    
    IndexBuffer myIB(indices, 3);
}

void display (void){
    
    glDrawArrays(GL_TRIANGLES, 0, 8);
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
    glewInit();
    
    init();
    
    while ( !glfwWindowShouldClose(window) ) {
        
        //display();
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}