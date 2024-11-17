//
// Created by Gian on 17/11/2024.
//

#ifndef TEST_OPENGL_CAMERACONTROLLER_H
#define TEST_OPENGL_CAMERACONTROLLER_H


#include "vec3.hpp"
#include "ext/matrix_float4x4.hpp"

class CameraController {
public:
    CameraController();

    CameraController(const glm::vec3 &cameraPosition, float w, float h);

    CameraController(float w, float h);

private:
    //glm::vec3 m_TranslateVector = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_CameraPosition;
    glm::mat4 m_View;
    float m_Width;
    float m_Height;
public:
    [[nodiscard]] glm::vec3 &getCameraPosition();



private:
    float m_FOV = 45.f;
    bool m_Ortographic = false;
public:
    float& getFOV();
    bool& IsOrtographic();
    glm::mat4 getView();
    glm::mat4 getProjection();




};


#endif //TEST_OPENGL_CAMERACONTROLLER_H
