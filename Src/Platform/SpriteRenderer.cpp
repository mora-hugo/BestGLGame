#include <SpriteRenderer.h>

void HC::SpriteRenderer::DrawSprite(const Sprite &sprite) const{
    Renderer::Draw();
    sprite.Draw();
}

HC::SpriteRenderer::SpriteRenderer(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
        : Renderer(vertexShaderPath, fragmentShaderPath) {

}

HC::SpriteRenderer::~SpriteRenderer() {

}
