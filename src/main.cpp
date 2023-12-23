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
#include "Math.hpp"

#include <iostream>


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
		zoom += -1.0;	

    else if (key == GLFW_KEY_SPACE) 
		zoom += 1.0;	        				
}

int main (void){
    glfwInit();
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "I'm a Window with a Cube!", NULL, NULL);
    
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    
    {
        float points[] = {
            //Coord              //Colors          //Textures
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, //0.0f, 0.0f, //0
            -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, //1.0f, 0.0f, //1
             0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, //1.0f, 1.0f, //2
            -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, //0.0f, 1.0f, //3
             0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, //0.0f, 0.0f, //4
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //1.0f, 0.0f, //5
             0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //1.0f, 1.0f, //6
            -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f  //,0.0f, 1.0f //7
        };

        unsigned int ind[] = {
          0, 2, 1,
          1, 2, 3,
          0, 4, 6,
          0, 6, 2,
          1, 4, 0,
          1, 5, 4,
          1, 3, 7,
          1, 7, 5,
          2, 6, 3,
          3, 6, 7,
          5, 6, 4,
          5, 7, 6
        };
        
        mat4f Mat;
        Quaternion rot(zoom, {1.0, 0.0, 0.0}); 
        Mat.RotateT(rot);

        mat4f t;
        t.TranslationT(0.0, 0.0, 4.0);
        mat4f y;
        y.TranslationT(0.0, 1.0, 0.0);

        float ar = (float)WIDTH / (float)HEIGHT;
        float Near = 0.0f;
        float Far = 10.0f;
        float Range = Near - Far;

        mat4f Proj(
                    1/ar, 0.0f, 0.0f, 0.0f,
                    0.0f, 1, 0.0f, 0.0f,
                    0.0f, 0.0f, (Far+Near)/Range, 2.0*Far*Near/Range,
                    0.0f, 0.0f, 1.0f, 0.0f
        );


        VertexArray myVAO;
        VertexBuffer Square(points, sizeof(points));

        VertexLayout layout;
        layout.Push<float>(3); //Coord
        layout.Push<float>(3); //Colors
        //layout.Push<float>(2); //TexCoord

        myVAO.AddBuffer(Square, layout);
        myVAO.Bind();

        IndexBuffer myIB(ind, 3*12);

        Shader shader("shader/vertex.shader", "shader/fragment.shader");
        shader.Bind();
        
        Renderer render;

        //Texture texture("textures/texture.jpg");
        //texture.Bind(0);

        //shader.SetUniform1i("u_Texture", 0);
        //shader.SetUniformMatrix4fv("t", translation);

        glfwSetKeyCallback(window, key_callback);

        while ( !glfwWindowShouldClose(window) ) {

            render.Clear();

            render.Draw(myVAO, myIB, shader);

            Quaternion rot(zoom, {1.0, 1.0, 0.0}); 
            Mat.RotateT(rot);
            shader.SetUniformMatrix4fv("t", Proj*t*Mat*y*Mat);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}