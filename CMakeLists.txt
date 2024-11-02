# CMakeList.txt : CMake project for test_opengl, include source and define
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("test_opengl")

add_subdirectory(dependencies/glew)
add_subdirectory(dependencies/glfw)

add_definitions(-DGLEW_STATIC)
add_executable (test_opengl "src/main/test_opengl.cpp"
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
        cmake-build-debug/Testing/Shader.cpp
        cmake-build-debug/Testing/Shader.h
        src/main/Shader.cpp
        src/main/Shader.h
        src/main/Asserts.h
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

target_link_libraries(test_opengl  glfw
	libglew_static)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET test_opengl PROPERTY CXX_STANDARD 20)
endif()


add_executable(test src/test/Test.cpp src/test/Test.h)
