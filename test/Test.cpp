//
// Created by gfiorini on 10/30/24.
//

#include "Test.h"

#include <cstring>
#include <iostream>
#include <ostream>
#include "stb_image/stb_image.h"



void test1() {
    std::cout << "sizeof(unsigned char): " << sizeof(unsigned char) << std::endl;
    std::cout << "sizeof(char): " << sizeof(char) << std::endl;
    std::cout << "sizeof(short int): " << sizeof(short int) << std::endl;
    std::cout << "sizeof(short int): " << sizeof(short int) << std::endl;
    std::cout << "sizeof(int): " << sizeof(int) << std::endl;
    std::cout << "sizeof(long): " << sizeof(long) << std::endl;
    std::cout << "sizeof(long long): " << sizeof(long long) << std::endl;
    std::cout << "sizeof(float) " << sizeof(float) << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << std::endl;
    std::cout << "sizeof(unsigned int): " << sizeof(unsigned int) << std::endl;
}

void test2() {
    int r = strcmp("abcd", "Abcd"); //return 0 if equal
    if (r) {
        std::cout << "strcmp(" << __FILE__ << ", " << __LINE__ << ") " << r << std::endl;
    }
}

void testMemory() {
    long long size = 8LL * 1024 * 1024 * 1024; // 8 GB

    char *buffer = (char *) malloc(size); // Allocate memory

    if (buffer == NULL) {
        return;
    }

    // Fill the buffer with data
    memset(buffer, 'A', size); // Fill with 'A'

    printf("Buffer filled. Press Enter to free memory and exit.\n");
    getchar(); // Wait for user input

    free(buffer); // Free allocated memory
}

void testStbImage() {
    char const * filename = "res/textures/flower.png";

    int x, y, channels;
    unsigned char* img = stbi_load(filename, &x, &y, &channels, 4);
    if (img == NULL) {
        std::cout << "stbi_load 2 failed" << std::endl;
    } else {
        std::cout << "stbi_load OK" << std::endl;
        std::printf("Image filename: %s, %dx%d pixels, #channels: %d", filename, x, y, channels);
    }
}

int main() {
    testStbImage();
}
