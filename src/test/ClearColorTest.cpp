//
// Created by gfiorini on 11/8/24.
//

#include "ClearColorTest.h"

#include <GL/gl.h>

#include "imgui.h"

namespace Test {
    ClearColorTest::ClearColorTest(Renderer &renderer) : m_clearColor{1.0, 1.0, 0.0, 1.0} , BaseTest(renderer){

    }

    ClearColorTest::~ClearColorTest() {
    }

    void ClearColorTest::OnUpdate(double deltaTime) {
        //std::cout << "ClearColorTest::OnUpdate: " << deltaTime << std::endl;
    }

    void ClearColorTest::OnRender() {
        glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void ClearColorTest::OnImGuiRender() {
        ImGui::ColorEdit4("Clear Color", m_clearColor);
    }




}