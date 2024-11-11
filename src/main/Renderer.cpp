//
// Created by gfiorini on 10/28/24.
//
#include <iostream>

#include "Renderer.h"

void GLAPIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id,
                                    GLenum severity, GLsizei length,
                                    const GLchar *message, const void *userParam) {
    std::cerr << "OpenGL Debug Message:\n";
    std::cerr << "Source: " << source << "\n";
    std::cerr << "Type: " << type << "\n";
    std::cerr << "ID: " << id << "\n";
    std::cerr << "Severity: " << severity << "\n";
    std::cerr << "Message: " << message << "\n\n";
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Renderer::Renderer(int winWidth, int winHeigth) {
    m_WinWidth = winWidth;
    m_WinHeigth = winHeigth;
}

void Renderer::EnableBlending() {
    glEnable(GL_BLEND); // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::EnableDebug() {
    glEnable(GL_DEBUG_OUTPUT); // Enable debug output
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Ensures callback is in sync with errors
    glDebugMessageCallback(openglDebugCallback, nullptr);
}

void Renderer::EnableDepthBuffer() {
    glEnable(GL_DEPTH_TEST);
}

void Renderer::DrawTriangles(const VertexArray &va, const IndexBuffer &ib, Shader &shader) {
    va.Bind();
    ib.Bind();
    shader.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
