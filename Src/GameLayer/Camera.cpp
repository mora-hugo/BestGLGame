#include <Camera.h>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext.hpp"
#include "Window.h"

Camera::Camera() {
    HC::Window::OnWindowResize.AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&Camera::OnWindowResized, this, 1));
}

Camera::~Camera() {

}

void Camera::SetPosition(const glm::vec2 &new_position) {
    position=new_position;
    bIsDirty = true;
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
    glm::vec2 windowSize = HC::Window::GetWindowSize();
    viewMatrix = glm::lookAt(glm::vec3(position.x,position.y, 30), glm::vec3(position.x,position.y, 0), glm::vec3(0.0f, 1.0f, 0.0f));
    projectionMatrix = glm::ortho((-windowSize.x / 2)*1/Zoom, (+windowSize.x / 2)*1/Zoom, (-windowSize.y/ 2)*1/Zoom, (+windowSize.y/ 2)*1/Zoom, 0.1f, 100.0f);
}

void Camera::Move(const glm::vec2 &offset) {
    SetPosition(GetPosition() + offset);
}

float Camera::GetZoom() const{
    return Zoom;
}

void Camera::SetZoom(float newZoom) {
    Zoom = newZoom;
    bIsDirty = true;
}

void Camera::OnWindowResized(const glm::vec2 &size) {
    UpdateMatrices();
}

glm::vec2 Camera::ScreenToWorld(const glm::vec2 &screenPosition) {
    glm::vec2 windowSize = HC::Window::GetWindowSize();
    //transform window position to world position (with 0,0 at the center)
    glm::vec3 worldPos = glm::unProject(glm::vec3(screenPosition.x, screenPosition.y, 1), glm::inverse(GetViewMatrix() * glm::mat4{ 1.f }),GetProjectionMatrix(), glm::vec4(0, 0, windowSize.x, windowSize.y)) + glm::vec3(GetPosition(), 1);
    worldPos.y = -worldPos.y;
    return glm::vec2(worldPos) + GetPosition();
}