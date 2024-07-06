#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct AABB {
    glm::vec2 start;
    float width, height;

    void Move(const glm::vec2& offset) {
        start += offset;
    }
};