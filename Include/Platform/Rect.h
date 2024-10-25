#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Rect {
    glm::vec2 start;
    float width, height;

    void Move(const glm::vec2& offset) {
        start += offset;
    }

    bool CollideWith(const Rect& OtherRect) {
        // collision x-axis?
        bool collisionX = start.x + width >= OtherRect.start.x &&
            OtherRect.start.x + OtherRect.width >= start.x;
        // collision y-axis?
        bool collisionY = start.y + height >= OtherRect.start.x &&
            OtherRect.start.y + OtherRect.height >= start.y;
        // collision only if on both axes
        return collisionX && collisionY;
    }
};