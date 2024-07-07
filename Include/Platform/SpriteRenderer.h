#pragma once

#include <Program.h>
#include <Sprite.h>
#include "Renderer.h"

namespace HC {
    class SpriteRenderer : public Renderer {
    public:
        SpriteRenderer(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~SpriteRenderer();

        SpriteRenderer(const SpriteRenderer&) = delete;
        SpriteRenderer &operator=(const SpriteRenderer&) = delete;

        void DrawSprite(const Sprite& sprite) const;

    };
}