//
// Created by gfiorini on 10/28/24.
//

#include "VertexBuffer.h"

#include <iostream>
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_RendererID);
    std::cout << "VertexBuffer deleted" << std::endl;
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
