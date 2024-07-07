#pragma once

#include <Renderer.h>
#include "TilesContainer.h"

namespace HC {
    class TileRenderer : public Renderer {
    public:
        TileRenderer(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~TileRenderer();

        TileRenderer(const TileRenderer&) = delete;
        TileRenderer &operator=(const TileRenderer&) = delete;

        void DrawTiles(const TilesContainer& tiles) const;
        //void DrawTile(const Tile& tile) const;
    };

}

