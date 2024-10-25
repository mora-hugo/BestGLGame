#pragma once

#include <Program.h>
#include <Sprite.h>
#include "Renderable.h"
namespace HC {
    class Renderer {
    public:
        Renderer(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Renderer();

        Renderer(const Renderer&) = delete;
        Renderer &operator=(const Renderer&) = delete;

        [[nodiscard]] const Program& GetProgram() const { return program; }

        void Draw(const IDrawable& renderable) const;
        static void ClearScreen(const glm::vec4 color);

    protected:
        Program program;
    };
}