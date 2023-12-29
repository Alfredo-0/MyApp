#include <GL/glew.h>

#include "../vendor/imgui/imgui.h"

#include "TestCube.hpp"
#include "../VertexArray.hpp"
#include "../VertexBuffer.hpp"
#include "../VertexLayout.hpp"
#include "../IndexBuffer.hpp"
#include "../Shader.hpp"
#include "../Math.hpp"
#include "../Renderer.hpp"


namespace  test {

    TestCube::TestCube()
        : m_Direction({0.0f, 0.0f, 0.0f}), m_Angle(0){
        
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

        Quaternion rot(0.0, {0.0, 0.0, 0.0}); 
        m_Rot.RotateT(rot);

        m_Trans.TranslationT(0.0, 0.0, 4.0);

        float ar = (float)600 / (float)600; //complete
        float Near = 0.0f;
        float Far = 10.0f;
        float Range = Near - Far;

        m_Proj = {
                    1/ar, 0.0f, 0.0f,             0.0f,
                    0.0f, 1.0f, 0.0f,             0.0f,
                    0.0f, 0.0f, (Far+Near)/Range, (float)(2.0*Far*Near/Range),
                    0.0f, 0.0f, 1.0f,             0.0f
        };

        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(points, sizeof(points));

        VertexLayout layout;
        layout.Push<float>(3); //Coord
        layout.Push<float>(3); //Colors

        m_VAO->AddBuffer(*m_VBO, layout);
        m_VAO->Bind();

        m_IBO = std::make_unique<IndexBuffer>(ind, 3*12);
        
        m_Shader = std::make_unique<Shader>("shader/vertex.shader", "shader/fragment.shader");
        m_Shader->Bind();
    }

    void TestCube::OnUpdate(float deltaTime) {}

    void TestCube::OnRender() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        Renderer renderer; 
        {
            Quaternion rot(m_Angle, m_Direction); 
            m_Rot.RotateT(rot);
            m_Shader->SetUniformMatrix4fv("t", m_Proj*m_Trans*m_Rot);
            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        }
    }

    void TestCube::OnImGuiRender() {
        ImGui::SliderFloat("x Coordinate", &m_Direction.x, 0.0f, 1.0f);
        ImGui::SliderFloat("y Coordinate", &m_Direction.y, 0.0f, 1.0f);
        ImGui::SliderFloat("z Coordinate", &m_Direction.z, 0.0f, 1.0f);
        ImGui::SliderFloat("Angle", &m_Angle, 0.0f, 360.0f);
    }
}