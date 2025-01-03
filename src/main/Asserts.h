//
// Created by gfiorini on 11/2/24.
//

#ifndef ASSERTS_H
#define ASSERTS_H

#include <GL/glew.h>
#include <csignal>

// Comment this out to disable debug messages

// Macro for debug messages
#ifdef DEBUG
#define DEBUG_PRINT(x) std::cout << "DEBUG: " << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif


#ifdef _MSC_VER  // MSVC
#include <intrin.h>
#define DEBUG_BREAK() __debugbreak()
#else  // GCC or Clang
#define DEBUG_BREAK() raise(SIGTRAP)
#endif

#define ASSERT(x) if (!x) DEBUG_BREAK();


#endif //ASSERTS_H
