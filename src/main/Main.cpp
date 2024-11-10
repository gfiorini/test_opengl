#include <ClearColorTest.h>
#include <complex>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "QuadTest.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "gtc/type_ptr.hpp"
#include "BaseTest.h"
#include "BlinkingTest.h"

Test::BaseTest *currentTest;

void window_size_callback(GLFWwindow *window, int width, int height) {
    if (currentTest != nullptr) {
        currentTest->OnResize(width, height);
    }
}



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

    window = glfwCreateWindow(width, height, "Sgrunt", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, window_size_callback);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Initialize ImGui OpenGL3 backend

    Renderer renderer(width, height);
    renderer.EnableBlending();
    renderer.EnableDebug();

    currentTest = nullptr;
    auto *testMenu = new Test::TestMenu(currentTest, renderer);

    testMenu->registerTest<Test::QuadTest>("Quad", renderer);
    testMenu->registerTest<Test::BlinkingTest>("Blink", renderer);
    testMenu->registerTest<Test::ClearColorTest>("Clear Color", renderer);

    double lastUpdate = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastUpdate;
        lastUpdate = currentTime;

        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest) {
            ImGui::Begin("Tests");
            if (currentTest != testMenu && ImGui::Button("<- Back to menu")) {
                delete currentTest;
                currentTest = testMenu;
            }

            currentTest->OnRender();
            currentTest->OnImGuiRender();
            currentTest->OnUpdate(deltaTime);

            ImGui::End();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
