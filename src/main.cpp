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
#include "Texture.hpp"

#include <iostream>
#include <cmath>

const double pi = std::acos(-1);
const unsigned int WIDTH = 500;
const unsigned int HEIGHT = 500;
float xPos, yPos;
float zoom = 1.;
float increment = .005f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_RELEASE) 
		return;

	if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_X)
		glfwSetWindowShouldClose(window, true);

	else if (key == GLFW_KEY_LEFT)
		xPos += 0.005;

    else if (key == GLFW_KEY_RIGHT)
		xPos += -0.005;

    else if (key == GLFW_KEY_UP) 
		yPos += -0.005;

    else if (key == GLFW_KEY_DOWN) 
		yPos += 0.005;

    else if (key == GLFW_KEY_KP_ADD) 
		zoom += 0.05;	

    else if (key == GLFW_KEY_SPACE) 
		zoom += -0.05;	        				
}

int main (void){
    glfwInit();
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "I'm a Shofis Window!", NULL, NULL);
    
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
        //  Coord         Textures    Colors
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //0
             0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //1
             0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, //2
            -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f  //3
        };

        unsigned int ind[] = {
            0, 1, 2,
            3, 2, 0
        };
        
        VertexArray myVAO;
        VertexBuffer Square(points, sizeof(points));

        VertexLayout layout;
        layout.Push<float>(2); //Coord
        layout.Push<float>(2); //TexCoord
        layout.Push<float>(3); //Colors

        myVAO.AddBuffer(Square, layout);

        myVAO.Bind();
        
        IndexBuffer myIB(ind, 6);

        Shader shader("shader/vertex.shader", "shader/fragment.shader");
        shader.Bind();
        
        Renderer render;
        //shader.SetUniform2f("resolution", (float)WIDTH, (float)HEIGHT);

        Texture texture("textures/texture.jpg");
        texture.Bind(0);

        shader.SetUniform1i("u_Texture", 0);

        glfwSetKeyCallback(window, key_callback);

        while ( !glfwWindowShouldClose(window) ) {

            render.Clear();

            //shader.SetUniform1f("zoom", zoom);
            //shader.SetUniform2f("position", xPos, yPos);

            render.Draw(myVAO, myIB, shader);
            /*
            if( zoom > 10.0f)
                increment = -0.005f;
            else if ( zoom < 1.0f )
                increment = 0.005f;
            zoom += increment;
            */
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}