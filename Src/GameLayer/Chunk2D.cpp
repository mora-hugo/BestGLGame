#include <Chunk2D.h>
#include <iostream>


HC::Chunk2D::Chunk2D() {
    CreateBuffers();
}

HC::Chunk2D::~Chunk2D() {

}

void HC::Chunk2D::GenerateBlocks() {
    for (int x = 0; x < TILES_X; x++) {
        for (int y = 0; y < TILES_Y; y++) {
            tiles[x * TILES_Y + y] = (x+y)%2;
        }
    }
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
