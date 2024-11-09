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
        void OnResize(int width, int height) override;
    private:
        types::Buffer m_BufferModel;
        Renderer& m_Renderer;
        std::unique_ptr<Shader> m_Shader;
        int m_Width;
        int m_Height;
    };
}


#endif //BLINKINGTEST_H
