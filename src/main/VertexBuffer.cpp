//
// Created by gfiorini on 10/28/24.
//

#include "VertexBuffer.h"

#include <iostream>
#include <GL/glew.h>

// VertexBuffer::VertexBuffer(const VertexBuffer& other) {
//     std::cout << "Copy constructor VertexBuffer\n";
// }

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    std::cout << "Creating VertexBuffer" << std::endl;
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}

VertexBuffer::~VertexBuffer() {
     std::cout << "Destroying VertexBuffer" << std::endl;
     glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

