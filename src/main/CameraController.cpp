//
// Created by Gian on 17/11/2024.
//

#include "CameraController.h"
#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"


CameraController::CameraController() : CameraController(glm::vec3(0.0f, 0.0f, 300.0f), 1920, 1080) {

}

CameraController::CameraController(float w, float h)  : CameraController(glm::vec3(0.0f, 0.0f, 300.0f), w, h){

}

CameraController::CameraController(const glm::vec3 &cameraPosition, float w, float h) : m_CameraPosition(cameraPosition){
    this->m_CameraPosition = cameraPosition;
    this->m_Width  = w;
    this->m_Height = h;
}

glm::vec3 &CameraController::getCameraPosition() {
    return m_CameraPosition;
}

float &CameraController::getFOV()  {
    return m_FOV;
}

glm::mat4 CameraController::getView() {
    return glm::lookAt(
            m_CameraPosition,
            glm::vec3(0.0f, 0.0f, 0.0f),    // Look at the origin
            glm::vec3(0.0f, 1.0f, 0.0f)     // Up vector
    );
}


glm::mat4 CameraController::getProjection() {

    if (m_Ortographic){
        return  glm::ortho(-static_cast<float>(m_Width)/2, static_cast<float>(m_Width/2), -static_cast<float>(m_Height/2), static_cast<float>(m_Height/2), -1.0f, 2000.0f);
    } else {
        return glm::perspective(
                glm::radians(m_FOV),   // Field of view in degrees
                (float) m_Width / m_Height, // Aspect ratio of the window
                0.1f,                  // Near clipping plane
                2000.0f                // Far clipping plane
        );
    }


}

bool &CameraController::IsOrtographic() {
    return m_Ortographic;
}




