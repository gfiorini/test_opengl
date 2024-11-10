//
// Created by gfiorini on 11/10/24.
//
#include <ClearColorTest.h>

#include "BaseTest.h"
#include "imgui.h"

namespace Test {

    TestMenu::TestMenu(BaseTest*& currentTestPointer, Renderer &renderer): BaseTest(renderer), m_CurrentTest(currentTestPointer) {
        if (currentTestPointer == nullptr) {
            m_CurrentTest = this;
        }
    }

    void TestMenu::OnRender() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void TestMenu::OnImGuiRender() {
        for (auto& test : m_Tests) {
            if (ImGui::Button(test.first.c_str())) {
                m_CurrentTest = test.second();
            }
        }
    }



}
