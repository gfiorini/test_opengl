//
// Created by gfiorini on 11/9/24.
//

#ifndef MODEL_H
#define MODEL_H
#include <memory>

#include "IndexBuffer.h"
#include "Types.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

inline types::Buffer loadQuad() {
    types::Vertex vertices[] = {
        {{-0, 0}, {0, 0}, {0, 0, 1}},
        {{100, -0}, {1, 0}, {1, 0, 0}},
        {{100, 100}, {1, 1}, {1, 1, 1},},
        {{0, 100}, {0, 1}, {0, 1, 1}},
    };

    unsigned int vertexIndices[]{
        0, 1, 2, // first triangle
        0, 2, 3 // second triangle
    };

    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout vbl;
    vbl.Push<float>(2);
    vbl.Push<float>(2);
    vbl.Push<float>(3);

    auto va = std::make_unique<VertexArray>() ;
    va->AddBuffer(vbo, vbl);

    auto ibo = std::make_unique<IndexBuffer>(vertexIndices, 6) ;
    return types::Buffer (std::move(ibo), std::move(va));
}

#endif //MODEL_H
