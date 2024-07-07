#pragma once

#include <Program.h>
#include <Sprite.h>
namespace HC {
    class Renderer {
    public:
        Renderer(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Renderer();

        Renderer(const Renderer&) = delete;
        Renderer &operator=(const Renderer&) = delete;
        static void ClearScreen(const glm::vec4 color);

        [[nodiscard]] const Program& GetProgram() const { return program; }
    protected:
        void Draw() const;
    protected:
        Program program;
    };
}