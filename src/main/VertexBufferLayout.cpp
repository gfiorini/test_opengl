//
// Created by gfiorini on 10/31/24.
//

#include <stdexcept>
#include "VertexBufferLayout.h"

template<typename T>
void VertexBufferLayout::Push(int count) {
#ifdef _MSC_VER  // MSVC
    throw std::runtime_error("Unsupported operation VertexBufferLayout::Push");
#else  // GCC or Clang
    static_assert(false);
#endif
}

template<>
void VertexBufferLayout::Push<float>(int count) {
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * sizeof(GL_FLOAT);
}