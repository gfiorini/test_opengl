//
// Created by gfiorini on 10/28/24.
//
#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Renderer {
    public:
        void EnableBlending();
        void EnableDebug();
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
        void Clear();
};