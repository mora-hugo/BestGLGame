#pragma once

#include <array>
#include <Renderable.h>

namespace HC {
    struct TilesContainer : public Renderable{
        friend class TileRenderer;
        static constexpr int TILES_X = 30;
        static constexpr int TILES_Y = 100;
        TilesContainer();
        ~TilesContainer() = default;
        

        TilesContainer(const TilesContainer&) = delete;
        TilesContainer& operator=(const TilesContainer&) = delete;

        std::array<uint16_t, TILES_X*TILES_Y> tiles = {0};

        void GenerateBlocks();
        void GenerateMesh();



    private:

        static inline const std::vector<Vertex> square_vertices = {
                // positions               // colors               // texture coords
                {{1.0f,  1.0f, 0.0f},   {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}},   // top right
                {{1.0f,  0.0f, 0.0f},   {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},   // bottom right
                {{0.0f,  0.0f, 0.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},   // bottom left
                {{0.0f,  1.0f, 0.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}    // top left
        };

        static inline const std::vector<GLuint> square_indices {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
        };





    };
}



