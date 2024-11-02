//
// Created by gfiorini on 11/2/24.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

class Texture {
public:
    explicit Texture(const std::string &filename);
    ~Texture();

    void Bind();
    void Unbind();

private:
    std::string filename;
    unsigned char* data;
    int width, height, channels;

};

#endif //TEXTURE_H
