#pragma once
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
class Camera {
public:
    Camera();
    ~Camera();


    void SetPosition(const glm::vec2& position);
    [[nodiscard]] const glm::vec2& GetPosition() const;

    [[nodiscard]] const glm::mat4& GetViewMatrix();
    [[nodiscard]] const glm::mat4& GetProjectionMatrix();

    void UpdateMatrices();

private:
    glm::vec2 position;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;


    bool bIsDirty;
};