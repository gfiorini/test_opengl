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
#include "Texture.h"

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
        0, 0,          0, 0,      1, 0, 0       ,// 0
        0.5f, 0,       1, 0,      0, 1, 0,       // 1
        0.5f, 0.5f,    1, 1,      1, 0, 1,      // 2
        0, 0.5f,       0, 1,      1, 1, 0       // 3
    };

    unsigned int vertexIndices[]{
        0, 1, 2, // first triangle
        0, 2, 3 // second triangle
    };

    Renderer renderer;
    renderer.EnableBlending();
    renderer.EnableDebug();

    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout vbl;
    vbl.Push<float>(2);
    vbl.Push<float>(2);
    vbl.Push<float>(3);

    VertexArray va;
    va.AddBuffer(vbo, vbl);

    IndexBuffer ibo = {vertexIndices, 6};



    Shader uvShader = Shader("res/shaders/uv.shader");
    Shader fixedColorShader = Shader("res/shaders/fixedColor.shader");
    Shader variableColorShader = Shader("res/shaders/variableColor.shader");
    Shader blinkingShader = Shader("res/shaders/blinking.shader");

    Texture t = Texture("res/textures/flower.png");
    t.Bind();

    Shader textureShader = Shader("res/shaders/textureShader.shader");
    textureShader.Bind();
    textureShader.SetUniform1i("u_Texture", 0);


    //v-sync ON
    glfwSwapInterval(1);

    bool isProg4 = false;
    float increment = 0.05f;
    float alphaProgram4 = 0;

    Shader currentShader = uvShader;
    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            currentShader = uvShader;
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            currentShader = fixedColorShader;
            isProg4 = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            currentShader = variableColorShader;
            isProg4 = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            currentShader = blinkingShader;
            isProg4 = true;
        } else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
            currentShader = textureShader;
            isProg4 = true;
        }

        // //todo: refactor logic
        if (isProg4) {
            if (alphaProgram4 > 1) {
                increment = -0.05f;
            } else if (alphaProgram4 < 0) {
                increment = 0.05f;
            }
            alphaProgram4 = alphaProgram4 + increment;
            currentShader.Bind();
            currentShader.SetUniform4v("u_Color", 0.0f, 0.5f, 0.2f, alphaProgram4);
        }

        renderer.Draw(va, ibo, currentShader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
