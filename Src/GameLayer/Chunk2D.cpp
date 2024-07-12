#include <Chunk2D.h>
#include <iostream>
#include <algorithm>


HC::Chunk2D::Chunk2D() {
    CreateBuffers();
    noise.SetFrequency(0.03f);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
}

HC::Chunk2D::~Chunk2D() {

}

void HC::Chunk2D::GenerateBlocks() {

    GenerateDefaultTerrain();
    GenerateCaves();

}

void HC::Chunk2D::GenerateMesh() {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::cout << position.x << " " << position.y << std::endl;

    for (int x = 0; x < TILES_X; x++) {
        for (int y = 0; y < TILES_Y; y++) {

            if (tiles[x * TILES_Y + y] == 1) {
                for (int i = 0; i < square_indices.size(); i++) {
                    indices.push_back(square_indices[i] + vertices.size() );
                }

                for (Vertex vertex : square_vertices) {
                    vertex.position *= Scale;
                    vertex.position +=  glm::vec3(position,0);
                    vertex.position -= (glm::vec3(-x, y, 0)*Scale);
                    vertices.push_back(vertex);
                }

            }
        }
    }

    BindBuffers(vertices, indices);
}

uint16_t HC::Chunk2D::GetTileAtLocation(const glm::ivec2 &RelativePosition) const {
    if(RelativePosition.x < 0 || RelativePosition.y < 0 || RelativePosition.x >= TILES_X || RelativePosition.y >= TILES_Y) {
        return 0;
    }
    return tiles[RelativePosition.x * TILES_Y + RelativePosition.y];
}

void HC::Chunk2D::GenerateDefaultTerrain() {
    int MaxHeightMap = TILES_X/1.5;
    for (int x = 0; x < TILES_X; x++) {

        const float XPos = (x* Scale + position.x) / Scale;
        const int Height = std::clamp<int>((noise.GetNoise(XPos, 0.f) + 1 ) * MaxHeightMap, 0, TILES_Y);
        for(int y = 0; y < Height; y++)
        {
            tiles[x * TILES_Y + y] = 0;
        }

        for(int y = Height; y < TILES_Y; y++)
        {
            tiles[x * TILES_Y + y] = 1;
        }
    }
}

void HC::Chunk2D::GenerateCaves() {
    FastNoiseLite caveNoise;
    caveNoise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
    caveNoise.SetFrequency(0.035f); // Ajuste la fréquence pour déterminer la taille des grottes

    for (float x = 0; x < TILES_X; x++) {
        for (float y = 0; y < TILES_Y; y++) {
            float noiseValue = caveNoise.GetNoise((x * Scale) +position.x, y);
            if(noiseValue > 0.7f) {
                tiles[x * TILES_Y + y] = 0;
            }

        }
    }
}
