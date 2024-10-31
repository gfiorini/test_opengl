//
// Created by gfiorini on 10/30/24.
//

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);

private:
    unsigned int m_RendererID;

};

#endif //VERTEXARRAY_H


