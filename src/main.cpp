//
//OpenGL
//Created by Alfredo
//
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexLayout.hpp"

#include <iostream>
#include <cmath>

const double pi = std::acos(-1);

int main (void){
    glfwInit();
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, World!", NULL, NULL);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    if (window == NULL){
        std::cout<<"Failed to create GLFW window!\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glewInit();
    
    {
        float points[] = {
             0.5,  0.5, //0
            -0.5,  0.5, //1
            -0.5, -0.5, //2
             0.5, -0.5, //3
        };
        
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };
        
        VertexArray myVAO;
        VertexBuffer myVBO(points, sizeof(points));

        VertexLayout layout;
        layout.Push<float>(2);
        myVAO.AddBuffer(myVBO, layout);

        myVAO.Bind();
        
        IndexBuffer myIB(indices, 6);

        Shader shader("shader/vertex.shader", "shader/fragment.shader");
        shader.Bind();
        
        
        float r = 0.;
        float increment = .005f;

        Renderer render;

        while ( !glfwWindowShouldClose(window) ) {

            render.Clear();

            shader.SetUniform4f("u_Color", r, r/2, .3f, 1.f);

            render.Draw(myVAO, myIB, shader);

            if( r > 1.0f)
                increment = -0.005f;
            else if ( r < 0.0f )
                increment = 0.005f;
            r += increment;
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}