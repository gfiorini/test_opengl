#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include "linmath.h"
#include <iostream>

// typedef struct Vertex
// {
//     vec2 pos;
//     vec3 col;
// } Vertex;
//
// static const Vertex vertices[3] =
// {
//     { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
//     { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
//     { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
// };

std::string srcSampleVertexShader = R"(
    #version 330 core
    layout(location = 0) in vec2 position;

    void main() {
        gl_Position = vec4(position, 0, 1.0);

    }
)";

std::string srcSampleFragmentShader = R"(
    #version 330 core
    out vec4 color;

    void main() {
        color = vec4(1, 0, 0, 0.3);
    }
)";

static unsigned int compileShader(unsigned int SHADER_TYPE, const std::string& source) {
    unsigned int shader = glCreateShader(SHADER_TYPE);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader " << SHADER_TYPE << " Compile Error: " << infoLog << std::endl;

    }
    return shader;
}

static unsigned int createProgram(const std::string& srcVertexShader, const std::string& srcFragmentShader) {
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, srcVertexShader);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, srcFragmentShader);

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

static unsigned int createSampleProgram() {
    return createProgram(srcSampleVertexShader, srcSampleFragmentShader);
}

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920*2, 1080*2, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    }
    fprintf(stdout, "GLEW Version: %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "OpenGl Version / Driver version: %s\n", glGetString(GL_VERSION));


    // vertix with pos and uvmap
    float vertices[] = {
        -0.5f, -0.5f, 0, 0,
        0.5f, -0.5f, 0, 0,
        0.0f,  0.5f, 0, 0,
    };

    constexpr GLsizei n = 1;
    GLuint vertexBuffer;

    glEnable(GL_BLEND); // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // create buffer to store vertexes
    glGenBuffers(n, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // copy vertexes in buffer (in graphic card)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // size = num element in index (position = 2 elements, uv = 2 elements)
    // stride = size in bytes of vertex 2*2 float (position) + 2*2 float (uv coords)
    // pointer = offest size, position = 0, uvmap = 8 = 2 * 4bytes (1 float = 32bit = 4 bytes)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);


    unsigned int sampleProgram = createSampleProgram();
    glUseProgram(sampleProgram);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);

}
