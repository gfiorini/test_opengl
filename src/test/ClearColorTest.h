//
// Created by gfiorini on 11/8/24.
//

#ifndef BASICCOLORTEST_H
#define BASICCOLORTEST_H
#include "BaseTest.h"

namespace Test {
    class ClearColorTest : public BaseTest {
    public:
        ClearColorTest(Renderer &renderer);
        ~ClearColorTest() override;

        void OnUpdate(double deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        float m_clearColor[4];
    };
}

#endif //BASICCOLORTEST_H
