//
// Created by gfiorini on 11/11/24.
//

#include "CubeTest.h"

#include "imgui.h"
#include "model.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"

namespace Test {
        CubeTest::CubeTest(Renderer &r) : BaseTest(r) {
        //todo: come riciclare shader già compilati ?
        m_Shader = std::make_unique<Shader>("res/shaders/uv.shader");
        m_BufferModel = loadCube();
    }

    void CubeTest::OnUpdate(double deltaTime) {
        //m_Model = rotate(m_Model, glm::radians((float)deltaTime * m_RotationSpeed * 10), glm::vec3(0, 1, 1));
        m_Model = rotate(m_Model, glm::radians((float)deltaTime * m_RotationSpeed * 10), glm::vec3(m_RotationAngle[0], m_RotationAngle[1], m_RotationAngle[2]));
    }

    void CubeTest::OnRender() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Shader->Bind();
        //auto mvp = glm::perspective(m_Camera_Settings[0], (float)m_Width / (float)m_Height, m_Camera_Settings[1], m_Camera_Settings[2]);
        glm::mat<4, 4, float> proj = glm::ortho(-m_Width/2, m_Width/2, -m_Height/2, m_Height/2, -150.0f, 150.0f);
        glm::mat<4, 4, float> view = translate(glm::mat4(1.0f), -m_TranslateVector);
        glm::mat<4, 4, float> mvp = proj * view * m_Model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer.DrawTriangles(*m_BufferModel.va, *m_BufferModel.ibo, *m_Shader);
    }

    void CubeTest::OnImGuiRender() {
            //ImGui::SliderFloat3("Camera", m_Camera_Settings, -100, 100);
            ImGui::SliderFloat("camera horizontal", &m_TranslateVector.x, -(m_Width/2)+100, (m_Width)/2);
            ImGui::SliderFloat("camera vertical", &m_TranslateVector.y, -(m_Height/2)+100, m_Height/2);
            ImGui::SliderFloat("rotation speed", &m_RotationSpeed, 0,100);
            ImGui::SliderFloat3("rotation angle", m_RotationAngle, 0, 1);

    }
}
