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
    
    GLFWwindow* window = glfwCreateWindow(600, 600, "I'm a Mandelbrot Set!", NULL, NULL);
    
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
             1,  1, //0
            -1,  1, //1
            -1, -1, //2
             1, -1, //3
        };

        float star[20];

        for(int i=0; i<5; ++i){
            star[2*i] = cos(2*pi*i/5)/2;
            star[2*i+1] = sin(2*pi*i/5)/2;
        };

        for(int i=0; i<5; ++i){
            star[2*i+10] = cos(2*pi*i/5 + pi/5)/6;
            star[2*i+11] = sin(2*pi*i/5 + pi/5)/6;
        };

        unsigned int ind[] = {
            0, 1, 2,
            3, 2, 0
        };

        unsigned int indices[] = {
            9, 0, 5,
            5, 1, 6,
            6, 2, 7,
            7, 3, 8,
            8, 4, 9
        };
        
        VertexArray myVAO;
        //VertexBuffer myVBO(star, sizeof(star));
        VertexBuffer Square(points, sizeof(points));

        VertexLayout layout;
        layout.Push<float>(2);
        myVAO.AddBuffer(Square, layout);

        myVAO.Bind();
        
        IndexBuffer myIB(ind, 6);

        Shader shader("shader/vertex.shader", "shader/fragment.shader");
        shader.Bind();
        
        
        float r = 0.;
        float increment = .005f;

        Renderer render;

        while ( !glfwWindowShouldClose(window) ) {

            render.Clear();

            shader.SetUniform2f("resolution", 600., 600.);

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