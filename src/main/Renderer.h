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
        void EnableDepthBuffer();
        void DrawTriangles(const VertexArray& va, const IndexBuffer& ib, Shader& shader);
        void Clear();
        Renderer(int winWidth, int winHeigth);
private:
    int m_WinWidth, m_WinHeigth;

    public:
        [[nodiscard]] int GetWinWidth() const {
            return m_WinWidth;
        }

        [[nodiscard]] int GetWinHeigth() const {
            return m_WinHeigth;
        }
};