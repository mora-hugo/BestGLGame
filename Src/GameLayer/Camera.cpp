#include <Camera.h>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::SetPosition(const glm::vec2 &position) {

}

const glm::vec2 &Camera::GetPosition() const {
    return position;
}

const glm::mat4 &Camera::GetViewMatrix() {
    if(bIsDirty) {
        UpdateMatrices();
    }
    return viewMatrix;
}

const glm::mat4 &Camera::GetProjectionMatrix() {
       if(bIsDirty) {
            UpdateMatrices();
       }
       return projectionMatrix;
}

void Camera::UpdateMatrices() {
    bIsDirty = false;
    viewMatrix = glm::lookAt(glm::vec3(position.x,position.y, 1), glm::vec3(position.x,position.y, 0), glm::vec3(0.0f, 1.0f, 0.0f));
    projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
}
