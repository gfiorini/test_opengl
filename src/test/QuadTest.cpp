//
// Created by gfiorini on 11/8/24.
//

#include "Types.h"
#include "QuadTest.h"
#include "Renderer.h"
#include <GL/gl.h>

#include "model.h"
#include "ext/matrix_clip_space.hpp"

namespace Test {
    QuadTest::QuadTest(Renderer &renderer) : m_Renderer(renderer) {
        m_Width = m_Renderer.GetWinWidth();
        m_Height = m_Renderer.GetWinHeigth();
        //todo: come riciclare shader già compilati ?
        m_Shader = std::make_unique<Shader>("res/shaders/fixedColor.shader");
        m_BufferModel = loadQuad();
    }

    QuadTest::~QuadTest() {
    }

    void QuadTest::OnUpdate(double deltaTime) {
    }

    void QuadTest::OnRender() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Shader->Bind();
        auto mvp = glm::ortho(0.0f, static_cast<float>(m_Width), 0.0f, static_cast<float>(m_Height), -1.0f, 1.0f);
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer.Draw(*m_BufferModel.va, *m_BufferModel.ibo, *m_Shader);
    }

    void QuadTest::OnImGuiRender() {
    }

    void QuadTest::OnResize(int width, int height) {
        m_Width = width;
        m_Height = height;
    }
}
