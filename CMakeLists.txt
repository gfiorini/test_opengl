﻿# CMakeList.txt : CMake project for test_opengl, include source and define
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

project("test_opengl")

add_subdirectory(dependencies/glew)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/assimp)


add_definitions(-DGLEW_STATIC)
add_executable(test_opengl "src/main/Main.cpp"
        dependencies/stb_image/stb_image.h
        dependencies/stb_image/stb_image.cpp
        dependencies/imgui/backends/imgui_impl_glfw.cpp
        dependencies/imgui/backends/imgui_impl_glfw.h
        dependencies/imgui/backends/imgui_impl_opengl3.cpp
        dependencies/imgui/backends/imgui_impl_opengl3.h
        dependencies/imgui/imgui_tables.cpp
        dependencies/imgui/imgui_widgets.cpp
        dependencies/imgui/imstb_rectpack.h
        dependencies/imgui/imstb_textedit.h
        dependencies/imgui/imstb_truetype.h
        dependencies/imgui/imgui.cpp
        dependencies/imgui/imgui_draw.cpp
        dependencies/imgui/imgui_internal.h
        dependencies/imgui/imconfig.h
        dependencies/imgui/imgui.h
        src/main/Renderer.cpp
        src/main/Renderer.h
        src/main/VertexBuffer.cpp
        src/main/VertexBuffer.h
        src/main/IndexBuffer.cpp
        src/main/IndexBuffer.h
        src/main/VertexArray.cpp
        src/main/VertexArray.h
        src/main/VertexBufferLayout.cpp
        src/main/VertexBufferLayout.h
        src/main/Shader.cpp
        src/main/Shader.h
        src/main/Asserts.h
        src/main/Texture.h
        src/main/Texture.cpp
        src/main/Types.h
        src/main/model.h
        src/test/ClearColorTest.cpp
        src/test/QuadTest.cpp
        src/test/QuadTest.h
        src/test/BlinkingTest.cpp
        src/test/BlinkingTest.h
        src/test/TestMenu.cpp
        src/test/CubeTest.cpp
        src/test/CubeTest.h
        src/test/TexturedCubeTest.cpp
        src/test/TexturedCubeTest.h
        src/main/CameraController.cpp
        src/main/CameraController.h
        src/main/model.cpp
)

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}")
file(COPY "${RESOURCE_DIR}" DESTINATION "${OUTPUT_DIR}")

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${RESOURCE_DIR}" "${OUTPUT_DIR}/res"
        DEPENDS ${RESOURCE_DIR}
)

target_include_directories(test_opengl PUBLIC dependencies/glfw/deps)
target_include_directories(test_opengl PUBLIC dependencies/glfw/include)
target_include_directories(test_opengl PUBLIC dependencies/glew/include)
target_include_directories(test_opengl PUBLIC dependencies/glm/glm)
target_include_directories(test_opengl PUBLIC dependencies/imgui)
target_include_directories(test_opengl PUBLIC dependencies/assimp/include)
target_include_directories(test_opengl PUBLIC dependencies/)
target_include_directories(test_opengl PUBLIC src/test)
target_include_directories(test_opengl PUBLIC src/main)

target_link_libraries(test_opengl glfw libglew_static glm assimp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET test_opengl PROPERTY CXX_STANDARD 20)
endif ()

add_executable(test test/TestMain.cpp
        dependencies/stb_image/stb_image.h
        dependencies/stb_image/stb_image.cpp
        test/TestMain.cpp
        test/tests/Test1.cpp
        test/Tests.h
        test/tests/TestLambda.cpp)

target_include_directories(test PUBLIC src/main)
target_include_directories(test PUBLIC dependencies)
