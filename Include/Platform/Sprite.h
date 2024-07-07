#pragma once
#include <glm/vec2.hpp>
#include <AABB.h>
#include <glad/glad.h>
#include <vector>
#include <string>
#include <Renderable.h>
namespace HC {



    struct Sprite : public Renderable {
        friend class SpriteRenderer;

        AABB spriteAABB;
        Sprite(AABB aabb, const std::string& texturePath);
        Sprite(AABB aabb);
        void Update();


    };

}
