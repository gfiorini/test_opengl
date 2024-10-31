//
// Created by gfiorini on 10/31/24.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const std::string &filepath) : m_Filepath(filepath), m_RendererID(0) {
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const {
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
    enum ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::stringstream shaders[2];

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Could not open shader file" << std::endl;
    }

    ShaderType shaderType = NONE;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("#vertex shader") != std::string::npos) {
            shaderType = VERTEX;
        } else if (line.find("#fragment shader") != std::string::npos) {
            shaderType = FRAGMENT;
        } else {
            if (shaderType != NONE) {
                shaders[shaderType] << line << std::endl;
            }
        }
    }

    ShaderProgramSource result;
    result.vertexSource = shaders[0].str();
    result.fragmentSource = shaders[1].str();

    DEBUG_PRINT("VERTEX SHADER SOURCE" << std::endl << result.vertexSource << std::endl);
    DEBUG_PRINT("FRAGMENT SHADER SOURCE" << std::endl << result.fragmentSource << std::endl);

    file.close();
    return result;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {

    unsigned int shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::cerr << "Shader " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") <<
                " Compile Error, log length: " << length << " chars" << std::endl;

        std::vector<char> infoLog(length);
        char *info_log = infoLog.data();
        glGetShaderInfoLog(shader, length, nullptr, info_log);
        std::cerr << "Shader " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Compile Error: " << info_log
                << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

unsigned int Shader::CreateShader(const std::string &srcVertexShader, const std::string &srcFragmentShader) {
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, srcVertexShader);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, srcFragmentShader);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader Program Linking Error: " << infoLog << std::endl;
    }

    // Delete the shaders as they’re linked into the program now and no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) == m_UniformLocationCache.end()) {
        m_UniformLocationCache[name] = glGetUniformLocation(m_RendererID, name.c_str());
    }
    return m_UniformLocationCache[name];
}

void Shader::SetUniform4v(const std::string &name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
