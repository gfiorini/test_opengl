//
// Created by gfiorini on 11/8/24.
//
#ifndef TYPES_H
#define TYPES_H
#include "IndexBuffer.h"
#include "VertexArray.h"
#include <memory>

namespace types {

    struct Position {
        float x;
        float y;
    };

    struct Color {
        float r;
        float g;
        float b;
    };

    struct UV {
        float u;
        float v;
    };

    struct Vertex {
        Position position;
        UV uv;
        Color color;
    };

    struct Buffer {
        std::unique_ptr<IndexBuffer> ibo;
        std::unique_ptr<VertexArray> va;
    };

}

#endif //TYPES_H
