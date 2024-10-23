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
add_executable (test_opengl "src/test_opengl.cpp" )

target_include_directories(test_opengl PUBLIC dependencies/glfw/include)
target_include_directories(test_opengl PUBLIC dependencies/glew/include)

target_link_libraries(test_opengl  glfw
	libglew_static  )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test_opengl PROPERTY CXX_STANDARD 20)
endif()


