#include <GL/glew.h>

#include "../vendor/imgui/imgui.h"

#include "TestMandelbrot.hpp"

#include "../VertexArray.hpp"
#include "../VertexBuffer.hpp"
#include "../VertexLayout.hpp"
#include "../IndexBuffer.hpp"
#include "../Shader.hpp"
#include "../Renderer.hpp"


namespace  test {

    TestMandelbrot::TestMandelbrot()
        : m_WIDTH(600.0f), m_HEIGHT(600.0f), m_Zoom(1.0f), 
          m_xPos(0.0f), m_yPos(0.0f){
        
        float points[] = {
             1.0,  1.0,
            -1.0, -1.0,
             1.0, -1.0,
            -1.0,  1.0,
        };

        unsigned int indices[] = {
            0, 1, 3,
            0, 2, 1
        };

        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(points, sizeof(points));

        VertexLayout layout;
        layout.Push<float>(2); //Coord

        m_VAO->AddBuffer(*m_VBO, layout);
        m_VAO->Bind();

        m_IBO = std::make_unique<IndexBuffer>(indices, 6);
        
        m_Shader = std::make_unique<Shader>("shader/Mvertex.shader", "shader/Mfragment.shader");
        m_Shader->Bind();
        m_Shader->SetUniform2f("resolution", (float)m_WIDTH, (float)m_HEIGHT);

    }

    void TestMandelbrot::OnUpdate(float deltaTime) {}

    void TestMandelbrot::OnRender() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        Renderer renderer; 

        m_Shader->SetUniform1f("zoom", m_Zoom);
        m_Shader->SetUniform2f("position", m_xPos, m_yPos);
        //m_Shader->SetUniform4f("u_Color", m_xPos, m_yPos, m_xPos, 1.0);
        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        
    }

    void TestMandelbrot::OnImGuiRender() {
        ImGui::SliderFloat("x Coordinate", &m_xPos, 0.0f, 1.0f);
        ImGui::SliderFloat("y Coordinate", &m_yPos, 0.0f, 1.0f);
        ImGui::SliderFloat("Zoom", &m_Zoom, 1.0f, 4.0f);
    }
}