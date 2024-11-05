//
// Created by gfiorini on 11/2/24.
//

#include "Texture.h"
#include <iostream>
#include <GL/glew.h>
#include "stb_image/stb_image.h"

Texture::Texture(const std::string &path) : m_RendererID(0), m_FilePath(path.c_str()), m_Width(0), m_Height(0), m_BPP(0), m_Data(nullptr) {

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    m_Data = stbi_load(m_FilePath, &m_Width, &m_Height, &m_BPP, 4);

    if (!m_Data) {
        std::cerr << "Failed to load texture: " << m_FilePath << std::endl;
    } else {
        std::printf("Loaded texture: %s, %dx%d pixels, channels_in_file: %d \n", m_FilePath, m_Width, m_Height, m_BPP);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
        stbi_image_free(m_Data);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}


