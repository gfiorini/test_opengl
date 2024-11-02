//
// Created by gfiorini on 11/2/24.
//

#include "Texture.h"
#include <iostream>
#include <GL/glew.h>

#include "stb_image.h"

Texture::Texture(const std::string &path) : m_RendererID(0), m_FilePath(path.c_str()), m_Width(0), m_Height(0), m_BPP(0), m_Data(nullptr) {
    glGenTextures(1, &m_RendererID);
    stbi_set_flip_vertically_on_load(true);
    m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    this->m_FilePath = path.c_str();
    if (!m_Data) {
        std::cerr << "Failed to load texture: " << this->m_FilePath << std::endl;
    } else {
        std::printf("Loaded texture: %s, %dx%d pixels, channels_in_file: %d \n", this->m_FilePath, m_Width, m_Height, m_BPP);
    }
}

Texture::~Texture() {
}

void Texture::Bind(unsigned int slot) const{


}

void Texture::Unbind() {
}


