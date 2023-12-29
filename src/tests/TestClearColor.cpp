#include <GL/glew.h>

#include "../vendor/imgui/imgui.h"

#include "TestClearColor.hpp"


namespace  test {

    TestClearColor::TestClearColor()
    : m_Color {0.5f, 0.0f, 0.0f, 1.0f}{
        
    }
    TestClearColor::~TestClearColor() {

    }

    void TestClearColor::OnUpdate(float deltaTime) {

    }

    void TestClearColor::OnRender() {
        glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void TestClearColor::OnImGuiRender() {
        ImGui::ColorEdit4("Clear Color", m_Color);
    }
}