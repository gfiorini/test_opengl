//
// Created by gfiorini on 11/9/24.
//

#ifndef BLINKING2TEST_H
#define BLINKING2TEST_H
#include <BaseTest.h>

#include "Renderer.h"
#include "Types.h"

namespace Test {
    class BlinkingTest : public BaseTest {
    public:
        explicit BlinkingTest(Renderer& renderer);
        ~BlinkingTest() override;

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
        glm::vec3 m_translateVector;
        float m_Color[3];
        float m_Alpha;
        float m_BlinkSpeed;
        int m_Sign;
    };
}

#endif //BLINKING2TEST_H
