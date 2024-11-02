//
// Created by gfiorini on 11/2/24.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

class Texture {
public:
    explicit Texture(const std::string &path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind();

private:
    unsigned int m_RendererID;
    const char* m_FilePath;
    unsigned char* m_Data;
    int m_Width, m_Height, m_BPP;

};

#endif //TEXTURE_H
