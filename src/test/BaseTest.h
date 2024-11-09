//
// Created by gfiorini on 11/8/24.
//

#ifndef BASETEST_H
#define BASETEST_H
#include <iostream>

namespace Test {
    class BaseTest {
    public:
        BaseTest() = default;
        virtual ~BaseTest() = default;
        void virtual OnUpdate(double deltaTime) = 0;
        void virtual OnRender() = 0;
        void virtual OnImGuiRender() = 0;
        void virtual OnResize(int width, int height) = 0;
    };
}
#endif //GLTEST_H
