//
// Created by gfiorini on 10/28/24.
//

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer {
public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
private:
    unsigned int m_RendererID;
};

#endif //VERTEXBUFFER_H
