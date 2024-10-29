//
// Created by gfiorini on 10/28/24.
//
#pragma once

#include <GL/glew.h>


void GLAPIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id,
                                    GLenum severity, GLsizei length,
                                    const GLchar* message, const void* userParam);

