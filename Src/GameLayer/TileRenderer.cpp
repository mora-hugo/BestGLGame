#include <TileRenderer.h>


HC::TileRenderer::TileRenderer(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
        : Renderer(vertexShaderPath, fragmentShaderPath) {

}

HC::TileRenderer::~TileRenderer() {

}

void HC::TileRenderer::DrawTiles(const TilesContainer &tiles) const {
    Renderer::Draw();
    tiles.Draw();
}
