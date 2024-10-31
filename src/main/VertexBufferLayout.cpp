//
// Created by gfiorini on 10/31/24.
//

#include "VertexBufferLayout.h"

template<typename T>
void VertexBufferLayout::Push(int count) {
    static_assert(false);
}

template<>
void VertexBufferLayout::Push<float>(int count) {
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * sizeof(GL_FLOAT);
}