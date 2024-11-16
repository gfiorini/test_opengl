//
// Created by Gian on 16/11/2024.
//

#include <random>
#include "TexturedCubeTest.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "model.h"
#include "Texture.h"
#include "imgui.h"

Test::TexturedCubeTest::TexturedCubeTest(Renderer &r) : BaseTest(r) {
    m_Shader = std::make_unique<Shader>("res/shaders/textureShader.shader");
    m_BufferModel = loadCubeTextureable();

    int textureSlot = 0;
    m_Texture = std::make_unique<Texture>("res/textures/crate.jpg");
    m_Texture->Bind(textureSlot);

    m_Shader->Bind();
    m_Shader->SetUniform1i("u_Texture", textureSlot);

    std::random_device rd; // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<> tr(-1.0, 1.0);
    std::uniform_real_distribution<> rad(0.0, 1.0);

    for (auto& m_Model: m_Models) {
        double x = tr(gen) * 400;
        double y = tr(gen) * 400;
        double z = tr(gen) * 200;

        float rot_value = rad(gen) * 360;
        double rx = tr(gen);
        double ry = tr(gen);
        double rz = tr(gen);

        glm::vec3 v = glm::vec3(x,y,z);
        glm::vec3 vr = glm::vec3(rx,ry,rz);
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
    glm::mat4 view = glm::lookAt(
            glm::vec3(m_CameraPosition[0], m_CameraPosition[1], m_CameraPosition[2]),
            glm::vec3(0.0f, 0.0f, 0.0f),    // Look at the origin
            glm::vec3(0.0f, 1.0f, 0.0f)     // Up vector


    );
    drawCubes(view);


}

void Test::TexturedCubeTest::drawCubes(const glm::mat4 &view) {

    for (auto& m_Model: m_Models) {
        m_Model = rotate(m_Model, glm::radians(m_Rotation), glm::vec3(m_RotationAngle[0], m_RotationAngle[1], m_RotationAngle[2]));
        glm::mat4 proj = glm::perspective(
                glm::radians(m_FOV),   // Field of view in degrees
                (float) m_Width / m_Height, // Aspect ratio of the window
                0.1f,                  // Near clipping plane
                2000.0f                // Far clipping plane
        );
        glm::mat<4, 4, float> mvp = proj * view * m_Model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer.DrawTriangles(*m_BufferModel.va, *m_BufferModel.ibo, *m_Shader);

    }



}




void Test::TexturedCubeTest::OnImGuiRender() {
    ImGui::SliderFloat3("Camera position", &m_CameraPosition[0],  -1000, 1000);
    ImGui::SliderFloat("rotation", &m_Rotation, 0, 360);
    ImGui::SliderFloat("FOV", &m_FOV , 0, 180);
    ImGui::SliderFloat3("rotation angle", m_RotationAngle, -1, 1);
}

