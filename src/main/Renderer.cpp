//
// Created by gfiorini on 10/28/24.
//
#include <iostream>

#include "Renderer.h"



void GLAPIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id,
                                    GLenum severity, GLsizei length,
                                    const GLchar* message, const void* userParam) {
    std::cerr << "OpenGL Debug Message:\n";
    std::cerr << "Source: " << source << "\n";
    std::cerr << "Type: " << type << "\n";
    std::cerr << "ID: " << id << "\n";
    std::cerr << "Severity: " << severity << "\n";
    std::cerr << "Message: " << message << "\n\n";
}