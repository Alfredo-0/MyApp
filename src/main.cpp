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

#include "tests/Test.hpp"
#include "tests/TestClearColor.hpp"
#include "tests/TestCube.hpp"
#include "tests/TestMandelbrot.hpp"

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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    {   
      Renderer renderer;

      // Setup Dear ImGui context
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO();
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

      // Setup Platform/Renderer backends
      ImGui_ImplGlfw_InitForOpenGL(window, true);          // Seccond param install_callback=true will install GLFW callbacks and chain to existing ones.
      ImGui_ImplOpenGL3_Init();

      bool show_demo_window = false;
      bool show_another_window = true;
      ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
      
      test::Test* currentTest = nullptr;
      test::TestMenu* testMenu = new test::TestMenu(currentTest);
      currentTest = testMenu;

      testMenu -> RegisterTest<test::TestClearColor>("Clear Color");
      testMenu -> RegisterTest<test::TestCube>("Cube");
      testMenu -> RegisterTest<test::TestMandelbrot>("Mandelbrot");


      while ( !glfwWindowShouldClose(window) ) {  
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        renderer.Clear();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(currentTest){
          currentTest->OnUpdate(0.0f);
          currentTest->OnRender();
          ImGui::Begin("Test");
          if(currentTest != testMenu && ImGui::Button("<-")){
              delete currentTest;
              currentTest = testMenu;
          }
          currentTest->OnImGuiRender();
          ImGui::End();
        }

        if (show_demo_window)
          ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwPollEvents();
        glfwSwapBuffers(window);
      }
      delete currentTest;
      if (currentTest != testMenu)
        delete testMenu;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}