//
// Created by gfiorini on 11/8/24.
//

#ifndef BLINKINGTEST_H
#define BLINKINGTEST_H
#include "BaseTest.h"
#include "Renderer.h"
#include "Types.h"

namespace Test {
    class QuadTest : public BaseTest {
    public:
        explicit QuadTest(Renderer& renderer);
        ~QuadTest() override;

        void OnUpdate(double deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        types::Buffer m_BufferModel;
        std::unique_ptr<Shader> m_Shader;
    };
}


#endif //BLINKINGTEST_H
