//
// Created by gfiorini on 11/9/24.
//

#ifndef BLINKING2TEST_H
#define BLINKING2TEST_H
#include <BaseTest.h>

#include "Renderer.h"
#include "Types.h"
#include "vec3.hpp"

namespace Test {
    class BlinkingTest : public BaseTest {
    public:
        explicit BlinkingTest(Renderer& renderer);
        ~BlinkingTest() override;

        void OnUpdate(double deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        types::Buffer m_BufferModel;
        std::unique_ptr<Shader> m_Shader;
        glm::vec3 m_translateVector = glm::vec3(0.0f, 0.0f, 0.0f);
        float m_Color[3];
        float m_Alpha;
        float m_BlinkSpeed;
        int m_Sign;
    };
}

#endif //BLINKING2TEST_H
