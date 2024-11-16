//
// Created by Gian on 16/11/2024.
//

#ifndef TEST_OPENGL_TEXTUREDCUBETEST_H
#define TEST_OPENGL_TEXTUREDCUBETEST_H

#include "BaseTest.h"
#include "Renderer.h"
#include "Types.h"
#include "Texture.h"

namespace Test {
    class TexturedCubeTest : public BaseTest {
    public:
        explicit TexturedCubeTest(Renderer &r);

        void OnUpdate(double deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        types::Buffer m_BufferModel;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        glm::mat<4, 4, float> m_Models[10] = {};
        glm::vec3 m_TranslateVector = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 300.0f);
        float m_FOV = 90.f;
        float m_Rotation = 0;
        float m_RotationAngle[3] = {0,0,1};

        void drawCubes(const glm::mat4 &view);
    };

}



#endif //TEST_OPENGL_TEXTUREDCUBETEST_H