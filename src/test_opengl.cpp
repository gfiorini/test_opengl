#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>



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

        std::vector<char> infoLog(length);
        char* info_log = infoLog.data();
        glGetShaderInfoLog(shader, length, nullptr, info_log);
        std::cerr << "Shader " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Compile Error: " << info_log << std::endl;
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

//#define DEBUG  // Comment this out to disable debug messages

// Macro for debug messages
#ifdef DEBUG
#define DEBUG_PRINT(x) std::cout << "DEBUG: " << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif

void GLAPIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id,
                                    GLenum severity, GLsizei length,
                                    const GLchar* message, const void* userParam) {
    std::cerr << "OpenGL Debug Message:\n";
    std::cerr << "Source: " << source << "\n";
    std::cerr << "Type: " << type << "\n";
    std::cerr << "ID: " << id << "\n";
    std::cerr << "Severity: " << severity << "\n";
    std::cerr << "Message: " << message << "\n\n";
}

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 1024, "Hello World", NULL, NULL);
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
        0, 0, 1, 0, 0, // 0
        0.5f, 0,  0, 1, 0, // 1
        0.5f,  0.5f,  0, 0, 1, // 2
        0, 0.5f, 0, 1, 0 // 3
    };

    unsigned int vertexIndices[] {
        0, 1, 2, // first triangle
        2, 3, 0  // second triangle
    };

    glEnable(GL_BLEND); // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEBUG_OUTPUT);              // Enable debug output
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);  // Ensures callback is in sync with errors

    glDebugMessageCallback(openglDebugCallback, nullptr);

    // vertex array object (bind a buffer to a specific layout)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // buffer data
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // index data
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);

    ShaderProgramSource sps1 = readShader("res/shaders/shader1.shader");
    ShaderProgramSource sps2 = readShader("res/shaders/shader2.shader");
    ShaderProgramSource sps3 = readShader("res/shaders/shader3.shader");
    ShaderProgramSource sps4 = readShader("res/shaders/shader4.shader");


    unsigned int program1 = createProgram(sps1.vertexSource, sps1.fragmentSource);
    unsigned int program2 = createProgram(sps2.vertexSource, sps2.fragmentSource);
    unsigned int program3 = createProgram(sps3.vertexSource, sps3.fragmentSource);
    unsigned int program4 = createProgram(sps4.vertexSource, sps4.fragmentSource);
    GLint uniformColorLocation = glGetUniformLocation(program4, "u_Color");

    //v-sync ON
    glfwSwapInterval(1);

    bool isProg4 = false;
    float increment = 0.05f;
    float alphaProgram4 = 0;

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            glUseProgram(program1);
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            glUseProgram(program2);
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            glUseProgram(program3);
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            glUseProgram(program4);
            isProg4 = true;
        }

        //todo: refactor logic
        if (isProg4) {
            if (alphaProgram4 > 1) {
                increment = -0.05f;
            } else if (alphaProgram4 < 0) {
                increment = 0.05f;
            }
            alphaProgram4 = alphaProgram4 + increment;
            glUniform4f(uniformColorLocation, 0.0f, 0.5f, 0.2f, alphaProgram4);
        }



        // glDrawW
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program1);
    glDeleteProgram(program2);
    glDeleteProgram(program3);
    glDeleteProgram(program4);
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);

}
