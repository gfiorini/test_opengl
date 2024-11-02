//
// Created by gfiorini on 10/31/24.
//

#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H
#include <GL/glew.h>
#include <vector>
#include "Debug.h"


struct VertexBufferElement {
    int type;
    int count;
    unsigned char normalized;

    unsigned int GetTypeSize() {
        switch (type) {
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
public:
    template <typename T> void Push(int count);
    [[nodiscard]] inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }
    [[nodiscard]] inline int GetStride() const { return m_Stride; }

private:
    std::vector<VertexBufferElement> m_Elements;
    int m_Stride = 0;
};

#endif //VERTEXBUFFERLAYOUT_H
