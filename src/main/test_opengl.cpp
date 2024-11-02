#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 1024, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "GLEW Version: %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "OpenGl Version / Driver version: %s\n", glGetString(GL_VERSION));

    // vertix with pos and color
    float vertices[] = {
        0, 0, 1, 0, 0, // 0
        0.5f, 0, 0, 1, 0, // 1
        0.5f, 0.5f, 0, 0, 1, // 2
        0, 0.5f, 0, 1, 0 // 3
    };

    unsigned int vertexIndices[]{
        0, 1, 2, // first triangle
        2, 3, 0 // second triangle
    };

    Renderer renderer;
    renderer.EnableBlending();
    renderer.EnableDebug();

    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout vbl;
    vbl.Push<float>(2);
    vbl.Push<float>(3);

    VertexArray va;
    va.AddBuffer(vbo, vbl);

    IndexBuffer ibo = {vertexIndices, 6};

    Shader shader1 = Shader("res/shaders/shader1.shader");
    Shader shader2 = Shader("res/shaders/shader2.shader");
    Shader shader3 = Shader("res/shaders/shader3.shader");
    Shader shader4 = Shader("res/shaders/shader4.shader");

    //v-sync ON
    glfwSwapInterval(1);

    bool isProg4 = false;
    float increment = 0.05f;
    float alphaProgram4 = 0;

    Shader currentShader = shader1;
    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            currentShader = shader1;
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            currentShader = shader2;
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            currentShader = shader3;
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            currentShader = shader4;
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
            shader4.SetUniform4v("u_Color", 0.0f, 0.5f, 0.2f, alphaProgram4);
        }

        renderer.Draw(va, ibo, currentShader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
