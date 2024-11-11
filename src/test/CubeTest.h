//
// Created by gfiorini on 11/11/24.
//

#ifndef CUBETESTING_H
#define CUBETESTING_H
#include <BaseTest.h>

#include "Types.h"

namespace Test {
    class CubeTest : public BaseTest {
    public:
        explicit CubeTest(Renderer &r);

        void OnUpdate(double deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        types::Buffer m_BufferModel;
        std::unique_ptr<Shader> m_Shader;
        float m_CameraSettings[3] = {35.f, 0.1f, 100.0f};
        glm::mat<4, 4, float> m_Model = glm::mat4(1.0f);
        glm::vec3 m_TranslateVector = glm::vec3(0.0f, 0.0f, 0.0f);
        float m_RotationSpeed = 0;
        float m_RotationAngle[3] = {0,0,1};
    };

}




#endif //CUBETESTING_H
