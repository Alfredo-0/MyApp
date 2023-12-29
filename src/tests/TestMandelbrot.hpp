#pragma once

#include "Test.hpp"
#include "../VertexBuffer.hpp"
#include "../IndexBuffer.hpp"
#include "../VertexArray.hpp"
#include "../Shader.hpp"

#include <memory>

namespace  test {

    class TestMandelbrot : public Test{
    public:
        TestMandelbrot();
        
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        float m_WIDTH, m_HEIGHT, m_Zoom, m_xPos, m_yPos;

        std::unique_ptr<VertexArray> m_VAO; 
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
    };
}