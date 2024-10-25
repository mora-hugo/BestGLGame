#pragma once

#include <array>
#include <Renderable.h>
#include <unordered_map>
#include "FastNoiseLite.h"

namespace HC {

    namespace Tile {
        static inline uint16_t AIR = 0;
        static inline uint16_t DIRT = 1;

        namespace NearTileMask {
            static const inline uint8_t TOP = 1 << 0; // 0001
            static const inline uint8_t BOTTOM = 1 << 1; // 0010
            static const inline uint8_t LEFT = 1 << 2; // 0100
            static const inline uint8_t RIGHT = 1 << 3; // 1000

        }
    }

    struct Chunk2D : public Renderable{
        friend class TileRenderer;
        static constexpr int TILES_X = 30;
        static constexpr int TILES_Y = 100;
        static constexpr float Scale = 0.5f;
        Chunk2D();
        ~Chunk2D();
        

        Chunk2D(const Chunk2D&) = delete;
        Chunk2D& operator=(const Chunk2D&) = delete;

        std::array<uint16_t, TILES_X*TILES_Y> tiles = {0};

        glm::ivec2 position{0};

        void GenerateBlocks();
        void RebuildMeshIfNecessary();
        void SetTileAtLocation(const glm::ivec2& RelativePosition, uint16_t Tile);
        [[nodiscard]] uint16_t GetTileAtLocation(const glm::ivec2& RelativePosition) const;


    private:
        void GenerateMesh();

        void GenerateDefaultTerrain();
        void GenerateCaves();
        void ApplyTexturesCoords();
        uint8_t CalculateTileMask(const glm::ivec2& position) const;
    private:
        bool bIsDirty = false;
        FastNoiseLite noise;
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



