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
        {{-0, 0, 0}, {0, 0}, {0, 0, 1}},
        {{100, -0, 0}, {1, 0}, {1, 0, 0}},
        {{100, 100, 0}, {1, 1}, {1, 1, 1},},
        {{0, 100, 0}, {0, 1}, {0, 1, 1}},
    };

    unsigned int vertexIndices[]{
        0, 1, 2, // first triangle
        0, 2, 3 // second triangle
    };

    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(2);
    vbl.Push<float>(3);

    auto va = std::make_unique<VertexArray>() ;
    va->AddBuffer(vbo, vbl);

    auto ibo = std::make_unique<IndexBuffer>(vertexIndices, 6) ;
    return types::Buffer (std::move(ibo), std::move(va));
}

inline types::Buffer loadCube() {
    types::Vertex vertices[] = {
        {{-0, 0, -50}, {0, 0}, {0, 0, 1}},
        {{100, -0, -50}, {1, 0}, {1, 0, 0}},
        {{100, 100, -50}, {1, 1}, {1, 1, 1},},
        {{0, 100, -50}, {0, 1}, {0, 1, 1}},

        {{-0, 0, 50}, {0, 0}, {0.5, 0.5, 1}},
        {{100, -0, 50}, {1, 0}, {1, 0, 0}},
        {{100, 100, 50}, {1, 1}, {0.2, 0.2, 1},},
        {{0, 100, 50}, {0, 1}, {0, 1, 1}}
    };


    unsigned int vertexIndices[]{
        0, 1, 2, // first triangle
        0, 3, 2, // second triangle

        4, 5, 6,
        4, 6, 7,

        1, 5, 6,
        6, 2, 1,

        0, 7, 4,
        0, 3, 7,

        3, 2, 6,
        3, 6, 7,

        0, 1, 5,
        0, 5, 4
    };
    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vbl.Push<float>(2);
    vbl.Push<float>(3);

    auto va = std::make_unique<VertexArray>() ;
    va->AddBuffer(vbo, vbl);

    auto ibo = std::make_unique<IndexBuffer>(vertexIndices, 36) ;
    return types::Buffer (std::move(ibo), std::move(va));
}

#endif //MODEL_H
