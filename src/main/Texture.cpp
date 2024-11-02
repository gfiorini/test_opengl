//
// Created by gfiorini on 11/2/24.
//

#include "Texture.h"
#include <iostream>
#include "stb_image.h"



Texture::Texture(const std::string &filename) {
}

Texture::~Texture() {
}

void Texture::Bind() {
}

void Texture::Unbind() {
}

void testStbImage() {
    char const * filename = "res/textures/flower.png";

    int x, y, channels;
    unsigned char* img = stbi_load(filename, &x, &y, &channels, 4);
    if (img == NULL) {
        std::cout << "stbi_load failed" << std::endl;
    } else {
        std::cout << "stbi_load OK" << std::endl;
        std::printf("Image filename: %s, %dx%d pixels, #channels: %d", filename, x, y, channels);
    }
}