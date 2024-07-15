#include <Camera.h>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
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
    // Obtenez la taille de la fenêtre
    glm::vec2 windowSize = HC::Window::GetWindowSize();

    // Convertir la position de l'écran en coordonnées normalisées dans l'intervalle [-1, 1]
    glm::vec4 normalizedScreenPos;
    normalizedScreenPos.x = (2.0f * screenPosition.x) / windowSize.x - 1.0f;
    normalizedScreenPos.y = 1.0f - (2.0f * screenPosition.y) / windowSize.y;
    normalizedScreenPos.z = 0.0f;
    normalizedScreenPos.w = 1.0f;

    // Obtenir les matrices de vue et de projection
    const glm::mat4 &view = GetViewMatrix();
    const glm::mat4 &proj = GetProjectionMatrix();

    // Calculer l'inverse de la matrice de vue-projection
    glm::mat4 invViewProj = glm::inverse(proj * view);

    // Transformer les coordonnées normalisées en coordonnées du monde
    glm::vec4 worldPos = invViewProj * normalizedScreenPos;

    // Diviser par w pour obtenir les coordonnées 2D finales
    return glm::vec2(worldPos.x, worldPos.y);
}