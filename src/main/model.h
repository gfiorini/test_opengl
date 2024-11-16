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

        {{-50, -50, 50}, {0, 0}, {0, 0, 1}},
        {{50, -50, 50}, {1, 0}, {1, 0, 0}},
        {{50, 50, 50}, {1, 1}, {1, 1, 1},},
        {{-50, 50, 50}, {0, 1}, {0, 1, 1}},

        {{-50, -50, -50}, {1, 1}, {0, 0, 1}},
        {{50, -50, -50}, {1, 0}, {1, 0, 0}},
        {{50, 50, -50}, {1, 1}, {1, 1, 1},},
        {{-50, 50, -50}, {0, 1}, {0, 1, 1}}

    };


    unsigned int vertexIndices[]{
        0, 1, 2, // first triangle
        0, 3, 2, // second triangle

        6, 5, 4,
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

inline types::Buffer loadCubeTextureable() {


    types::Vertex vertices[] = {

            // face A
            {{-50, -50, 50}, {0, 0}, {0, 0, 1}}, // 0
            {{50, -50, 50}, {1, 0}, {1, 0, 0}}, // 1
            {{50, 50, 50}, {1, 1}, {1, 1, 1},}, // 2
            {{-50, 50, 50}, {0, 1}, {0, 1, 1}}, // 3

            // face B
            {{50, -50, 50}, {0, 0}, {1, 0, 0}}, // 4
            {{50, -50, -50}, {1, 0}, {1, 0, 0}}, // 5
            {{50, 50, -50}, {1, 1}, {0, 1, 1}}, // 6
            {{50, 50, 50}, {0, 1}, {1, 1, 1},}, // 7

            // face C
            {{-50, -50, 50}, {0, 0}, {0, 0, 1}}, // 8
            {{50, -50, 50}, {1, 0}, {1, 0, 0}}, // 9
            {{50, -50, -50}, {1, 1}, {1, 1, 1},}, // 10
            {{-50, -50, -50}, {0, 1}, {0, 1, 1}}, // 11

//
//            // face D
            {{-50, -50, -50}, {0, 0}, {0, 0, 1}}, // 12
            {{50, -50, -50}, {1, 0}, {1, 0, 0}}, // 13
            {{50, 50, -50}, {1, 1}, {1, 1, 1},}, // 14
            {{-50, 50, -50}, {0, 1}, {0, 1, 1}}, // 15

            // face E
            {{-50, -50, 50}, {0, 0}, {1, 0, 0}}, // 16
            {{-50, -50, -50}, {1, 0}, {1, 0, 0}}, // 17
            {{-50, 50, -50}, {1, 1}, {0, 1, 1}}, // 18
            {{-50, 50, 50}, {0, 1}, {1, 1, 1},}, // 19

            // face F
            {{-50, 50, 50}, {0, 0}, {0, 0, 1}}, // 20
            {{50, 50, 50}, {1, 0}, {1, 0, 0}}, // 21
            {{50, 50, -50}, {1, 1}, {1, 1, 1},}, // 22
            {{-50, 50, -50}, {0, 1}, {0, 1, 1}}, // 23
    };


    unsigned int vertexIndices[]{

            // Face A
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            8, 10, 9,
            8, 11, 10,

            12, 15, 14,
            12, 14, 13,

            18, 16, 19,
            18, 17, 16,

            20, 21, 22,
            20, 22, 23

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
