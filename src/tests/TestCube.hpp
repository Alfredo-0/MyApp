#pragma once

#include "Test.hpp"
#include "../VertexArray.hpp"
#include "../VertexBuffer.hpp"
#include "../VertexLayout.hpp"
#include "../Shader.hpp"
#include "../Texture.hpp"
#include "../Math.hpp"

#include <memory>

namespace  test {

    class TestCube : public Test{
    public:
        TestCube();
        
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        vec3f m_Direction;
        float m_Angle;
        mat4f m_Rot, m_Trans, m_Proj; 

        std::unique_ptr<VertexArray> m_VAO; 
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
    };
}