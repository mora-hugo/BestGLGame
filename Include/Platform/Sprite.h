#pragma once
#include <glm/vec2.hpp>
#include <Rect.h>
#include <glad/glad.h>
#include <vector>
#include <string>
#include <Renderable.h>
namespace HC {



    struct Sprite : public Renderable {
        friend class SpriteRenderer;

        Rect spriteAABB;
        Sprite(Rect aabb, const std::string& texturePath);
        Sprite(Rect aabb);
        void Update();


    };

}
