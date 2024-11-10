//
// Created by gfiorini on 11/9/24.
//

#include "BlinkingTest.h"

#include "imgui.h"
#include "model.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

namespace Test {

    BlinkingTest::BlinkingTest(Renderer &renderer) : BaseTest(renderer), m_Color{1,1,1}, m_Alpha(1.0f), m_BlinkSpeed(0), m_Sign(1) {
        m_Shader = std::make_unique<Shader>("res/shaders/variableColor.shader");
        m_BufferModel = loadQuad();
    }

    BlinkingTest::~BlinkingTest() {
    }

    void BlinkingTest::OnUpdate(double deltaTime) {
        m_Alpha += m_Sign * m_BlinkSpeed * deltaTime * 5 ;
        if (m_Alpha >= 1.0f) {
            m_Alpha = 1.0f;
            m_Sign *= -1;
        } else if (m_Alpha <= 0.0f) {
            m_Alpha = 0.0f;
            m_Sign *= -1;
        }
    }

    void BlinkingTest::OnRender() {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Shader->Bind();
        auto proj = glm::ortho(-(static_cast<float>(m_Width)/2), static_cast<float>(m_Width)/2, -(static_cast<float>(m_Height)/2), (static_cast<float>(m_Height)/2), -1.0f, 1.0f);
        auto view = translate(glm::mat4(1.0f), -m_translateVector);
        auto mvp = proj * view; // m = 1
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Shader->SetUniform4v("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Alpha);
        m_Renderer.Draw(*m_BufferModel.va, *m_BufferModel.ibo, *m_Shader);
    }

    void BlinkingTest::OnImGuiRender() {

        ImGui::SliderFloat("camera horizontal", &m_translateVector.x, -(m_Width/2)+100, (m_Width)/2);
        ImGui::SliderFloat("camera vertical", &m_translateVector.y, -(m_Height/2)+100, m_Height/2);
        ImGui::ColorEdit3("Color", m_Color);
        ImGui::SliderFloat("Blink speed", &m_BlinkSpeed, 0.0f, 1);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }


}
