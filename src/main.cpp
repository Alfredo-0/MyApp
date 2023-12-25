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
#include "OBJLoader.hpp"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <vector>

const unsigned int WIDTH  = 600;
const unsigned int HEIGHT = 600;


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
    
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

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
        Quaternion rot(0.0, {0.0, 0.0, 0.0}); 
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
                    1/ar, 0.0f, 0.0f,             0.0f,
                    0.0f, 1.0f, 0.0f,             0.0f,
                    0.0f, 0.0f, (Far+Near)/Range, 2.0*Far*Near/Range,
                    0.0f, 0.0f, 1.0f,             0.0f
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

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        ImGui_ImplOpenGL3_Init();

        bool show_demo_window = false;
        bool show_another_window = true;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        vec3f direction(0.0, 0.0, 0.0);
        float angle = 0;

        while ( !glfwWindowShouldClose(window) ) {
            
            render.Clear();
            
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (show_demo_window)
              ImGui::ShowDemoWindow(&show_demo_window);

            render.Draw(myVAO, myIB, shader);

            
            Quaternion rot(angle, direction); 
            Mat.RotateT(rot);
            shader.SetUniformMatrix4fv("t", Proj*t*Mat);
            
            {
              static float f = 0.0f;
              static int counter = 0;

              ImGui::Begin("My first IU!");

              ImGui::Text("Rotations");
              //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
              //ImGui::Checkbox("Another Window", &show_another_window);

              ImGui::SliderFloat("x Coordinate", &direction.x, 0.0f, 1.0f);
              ImGui::SliderFloat("y Coordinate", &direction.y, 0.0f, 1.0f);
              ImGui::SliderFloat("z Coordinate", &direction.z, 0.0f, 1.0f);
              ImGui::SliderFloat("Angle", &angle, 0.0f, 360.0f);

              ImGui::ColorEdit3("clear color", (float*)&clear_color);

              if (ImGui::Button("Button"))
                  counter++;
              ImGui::SameLine();
              ImGui::Text("counter = %d", counter);

              ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
              ImGui::End();
            }

            ImGui::Render();
        
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}