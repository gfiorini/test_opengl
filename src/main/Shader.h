//
// Created by gfiorini on 10/31/24.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {
public:
    explicit Shader(const std::string &filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4v(const std::string& name, float v0, float v1, float v2, float v3);

private:
    unsigned int m_RendererID;
    std::string m_Filepath;

    ShaderProgramSource ParseShader(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &srcVertexShader, const std::string &srcFragmentShader);
    int GetUniformLocation(const std::string& name);
};

#endif //SHADER_H