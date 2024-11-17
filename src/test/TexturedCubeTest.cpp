//
// Created by Gian on 16/11/2024.
//

#include <random>
#include "TexturedCubeTest.h"
#include "ext/matrix_transform.hpp"
#include "model.h"
#include "Texture.h"
#include "imgui.h"

Test::TexturedCubeTest::TexturedCubeTest(Renderer &r) : BaseTest(r) {
    m_Shader = std::make_unique<Shader>("res/shaders/textureShader.shader");
    m_BufferModel = loadCubeTextureable();

    int textureSlot = 0;
    m_Texture = std::make_unique<Texture>("res/textures/crate2.jpg");
    m_Texture->Bind(textureSlot);

    m_Shader->Bind();
    m_Shader->SetUniform1i("u_Texture", textureSlot);

    m_CameraController = CameraController(glm::vec3(800.0f, 800.0f, 800.0f), m_Width, m_Height);

    std::random_device rd; // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<> tr(-1.0, 1.0);
    std::uniform_real_distribution<> rad(0.0, 1.0);

    for (auto &m_Model: m_Models) {
        double x = tr(gen) * 600;
        double y = tr(gen) * 600;
        double z = tr(gen) * 200;

        float rot_value = rad(gen) * 360;
        double rx = tr(gen);
        double ry = tr(gen);
        double rz = tr(gen);

        glm::vec3 v = glm::vec3(x, y, z);
        glm::vec3 vr = glm::vec3(rx, ry, rz);
        m_Model = rotate(glm::mat4(1), glm::radians(rot_value), vr);
        m_Model = glm::translate(m_Model, v);
    }

    glEnable(GL_CULL_FACE);
}

void Test::TexturedCubeTest::OnUpdate(double deltaTime) {
    BaseTest::OnUpdate(deltaTime);
}

void Test::TexturedCubeTest::OnRender() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    m_Shader->Bind();
    drawCubes();
}

void Test::TexturedCubeTest::drawCubes() {
    for (auto &m_Model: m_Models) {
        m_Model = rotate(m_Model, glm::radians(m_Rotation),
                         glm::vec3(m_RotationAngle[0], m_RotationAngle[1], m_RotationAngle[2]));

        glm::mat<4, 4, float> mvp = m_CameraController.getProjection() * m_CameraController.getView() * m_Model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer.DrawTriangles(*m_BufferModel.va, *m_BufferModel.ibo, *m_Shader);
    }
}

void Test::TexturedCubeTest::OnScroll(int xoffset, int yoffset) {
    m_CameraController.getFOV() += -yoffset * 5;
    if (m_CameraController.getFOV() > FOV_MAX){
        m_CameraController.getFOV() = FOV_MAX;
    } else if (m_CameraController.getFOV() < 0){
        m_CameraController.getFOV() = 0;
    }
}


void Test::TexturedCubeTest::OnImGuiRender() {
    ImGui::Begin("Camera");
    ImGui::SliderFloat("FOV", &m_CameraController.getFOV(), 0, FOV_MAX);
    ImGui::SliderFloat3("Camera position", &m_CameraController.getCameraPosition()[0], -1000, 1000);
    ImGui::Checkbox("Is Ortographic", &m_CameraController.IsOrtographic());
    ImGui::End();

    ImGui::SliderFloat("rotation", &m_Rotation, 0, 10);
    ImGui::SliderFloat3("rotation angle", m_RotationAngle, -1, 1);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

