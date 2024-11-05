#include <complex>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "gtc/type_ptr.hpp"

struct Position {
    float x;
    float y;
};

struct Color {
    float r;
    float g;
    float b;
};

struct UV {
    float u;
    float v;
};

struct Vertex {
    Position position;
    UV uv;
    Color color;
};

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    int width = 1920;
    int height = 1080;
    float ratio = (float) width / (float) height;
    float inverseZoom = 1.0f;

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
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

    Vertex vertices[] = {
        {{-0, 0}, {0, 0}, {0, 0, 1}},
        {{100, -0}, {1, 0}, {1, 0, 0}},
        {{100, 100}, {1, 1}, {1, 1, 1},},
        {{0, 100}, {0, 1}, {0, 1, 1}},
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
    uvShader.Bind();

    Shader fixedColorShader = Shader("res/shaders/fixedColor.shader");
    fixedColorShader.Bind();

    Shader variableColorShader = Shader("res/shaders/variableColor.shader");
    variableColorShader.Bind();

    Shader blinkingShader = Shader("res/shaders/blinking.shader");
    blinkingShader.Bind();

    // Texture t = Texture("res/textures/flower.png");
    Texture t = Texture("res/textures/whatsapp.png");
    t.Bind();

    Shader textureShader = Shader("res/shaders/textureShader.shader");
    textureShader.Bind();
    textureShader.SetUniform1i("u_Texture", 0);
    textureShader.Unbind();

    //v-sync ON
    glfwSwapInterval(1);

    bool isProg4 = false;
    float increment = 0.05f;
    float alphaProgram4 = 0;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfwGL3_Init(window, true, "#version 330");

    Shader *currentShader = &uvShader;

    glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::vec3 translateVector(0.f, 0.f, 0.0f);
    glm::mat4 model;
    glm::mat4 mvp;

    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();
        model = translate(glm::mat4(1.0f), translateVector);
        mvp = proj * view * model;

        currentShader->SetUniformMat4f("u_MVP", mvp);

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            currentShader = &uvShader;
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            currentShader = &fixedColorShader;
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            currentShader = &variableColorShader;
            isProg4 = false;
        } else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            currentShader = &blinkingShader;
            isProg4 = true;
        } else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
            currentShader = &textureShader;
            isProg4 = false;
        }

        // //todo: refactor logic
        if (isProg4) {
            if (alphaProgram4 > 1) {
                increment = -0.05f;
            } else if (alphaProgram4 < 0) {
                increment = 0.05f;
            }
            alphaProgram4 = alphaProgram4 + increment;
            currentShader->Bind();
            currentShader->SetUniform4v("u_Color", 0.0f, 0.5f, 0.2f, alphaProgram4);
        }

        renderer.Draw(va, ibo, *currentShader);

        {
            ImGui::SliderFloat("horizontal", &translateVector.x, 0.0f, width - 100.f);
            ImGui::SliderFloat("vertical", &translateVector.y, 0.0f, height - 100.f);
            ImGui::SliderFloat("z-depth", &translateVector.z, -1.1f, 1.1f);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
