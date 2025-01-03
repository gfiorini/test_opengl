//
// Created by gfiorini on 10/29/24.
//
#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IndexBuffer {
public:
    //IndexBuffer(const IndexBuffer& cc);
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;
    [[nodiscard]] inline unsigned int GetCount() const { return m_Count; }

private:
    unsigned int m_RendererID;
    unsigned int m_Count;
};
#endif //INDEXBUFFER_H
