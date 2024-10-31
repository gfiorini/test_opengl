//
// Created by gfiorini on 10/30/24.
//

#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout) {
    Bind();
    vbo.Bind();
    int index = 0;
    std::uintptr_t offset = 0;
    for (VertexBufferElement vbe: layout.GetElements()) {
        glVertexAttribPointer(index, vbe.count, vbe.type, vbe.normalized, layout.GetStride(), (const void*)offset);
        glEnableVertexAttribArray(index);
        offset += vbe.count * vbe.GetTypeSize();
        index++;
    }
    vbo.Unbind();
    Unbind();
}

