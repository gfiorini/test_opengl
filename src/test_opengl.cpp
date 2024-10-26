#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

std::string srcSampleVertexShader = R"(
    #version 330 core
    layout(location = 0) in vec2 position;
    layout(location = 1) in vec3 color;

    out vec3 vColor;

    void main() {
        gl_Position = vec4(position, 0, 1.0);
        vColor = color;
    }
)";

std::string srcSampleFragmentShader = R"(
    #version 330 core
    out vec4 color;

    void main() {
        color = vec4(1, 0, 0, 0.3);
    }
)";

std::string srcSampleFragmentShader2 = R"(
    #version 330 core
    out vec4 color;

    void main() {
        color = vec4(1, 0, 0, 1);
    }
)";

std::string srcSampleFragmentShader3 = R"(
    #version 330 core
    in vec4 vColor;
    out vec4 color;

    void main() {
        color = vColor;
    }
)";

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

static unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::cerr << "Shader " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") <<
            " Compile Error, log length: " << length << " chars" << std::endl;

        char infoLog[length];
        glGetShaderInfoLog(shader, length, nullptr, infoLog);
        std::cerr << "Shader " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Compile Error: " << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
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

#define DEBUG  // Comment this out to disable debug messages

// Macro for debug messages
#ifdef DEBUG
#define DEBUG_PRINT(x) std::cout << "DEBUG: " << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif

ShaderProgramSource readShader(const std::string& filepath) {

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


    // vertix with pos and color
    float vertices[] = {
        -0.5f, -0.5f, 1, 0, 0,
        0.5f, -0.5f,  0, 1, 0,
        0.0f,  0.5f,  0, 0, 1
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    readShader("res/shaders/shader1.shader");

    unsigned int program1 = createProgram(srcSampleVertexShader, srcSampleFragmentShader);
    unsigned int program2 = createProgram(srcSampleVertexShader, srcSampleFragmentShader2);
    unsigned int program3 = createProgram(srcSampleVertexShader, srcSampleFragmentShader3);

    glUseProgram(program1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            glUseProgram(program1);
        } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            glUseProgram(program2);
        } else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            glUseProgram(program3);
        }

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program1);
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);

}
