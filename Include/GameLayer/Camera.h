#pragma once
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <Window.h>
class Camera {
public:
    Camera();
    ~Camera();

    void SetZoom(float newZoom);
    void SetPosition(const glm::vec2& position);
    void Move(const glm::vec2& offset);
    [[nodiscard]] const glm::vec2& GetPosition() const;

    [[nodiscard]] const glm::mat4& GetViewMatrix();
    [[nodiscard]] const glm::mat4& GetProjectionMatrix();
    [[nodiscard]] float GetZoom() const;
    void UpdateMatrices();
    glm::vec2 ScreenToWorld(const glm::vec2& ScreenPosition);


private:
    void OnWindowResized(const glm::vec2& size);
private:
    glm::vec2 position{0.f};

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    float Zoom = 55.f;


    bool bIsDirty = true;
};