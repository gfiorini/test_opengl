//
// Created by gfiorini on 10/29/24.
//
#include "IndexBuffer.h"
#include <cassert>
#include <iostream>
#include <GL/glew.h>

// IndexBuffer::IndexBuffer(const IndexBuffer &cc) {
//     std::cout << "Copy constructor IndexBuffer" << std::endl;
// }

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count) {
    std::cout << "Creating IndexBuffer" << std::endl;
    assert(sizeof(unsigned int) == sizeof(GLuint));
    m_Count = count;
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    std::cout << "Destroying IndexBuffer\n";
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
