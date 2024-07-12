#include <iostream>
#include "ChunkManager2D.h"
#include "Rect.h"
void HC::ChunkManager2D::Draw() const
{
	for (auto& ChunkPair : Chunks) {
		if (ChunkPair.second) {
			ChunkPair.second->Draw();
		}
	}
}

void HC::ChunkManager2D::LoadChunk(const glm::ivec2& ChunkPosition)
{
	if (Chunks.find(ChunkPosition) != Chunks.end()) {
		//Chunk already loaded
		return;
	}
	auto ChunkPtr = std::make_unique<Chunk2D>();
	glm::vec2 WorldChunkPosition = glm::vec2(ChunkPosition) * Chunk2D::Scale * static_cast<float>(Chunk2D::TILES_X);
	WorldChunkPosition.y = (Chunk2D::TILES_Y * Chunk2D::Scale) / 2;
	ChunkPtr->position = WorldChunkPosition;
	ChunkPtr->GenerateBlocks();
	ChunkPtr->GenerateMesh();
	Chunks.insert({ ChunkPosition, std::move(ChunkPtr) });


}

void HC::ChunkManager2D::LoadChunks(const std::vector<glm::ivec2>& ChunksPositions, bool AutoUnloadOtherChunks)
{
    if (!AutoUnloadOtherChunks) {
        for (const glm::ivec2& ChunkPos : ChunksPositions) {
            LoadChunk(ChunkPos);
        }
        return;
    } else {
        std::vector<glm::ivec2> NewChunksPositions = ChunksPositions;
        std::vector<glm::ivec2> ChunksToUnload;

        for (const auto& ChunkPair : Chunks) {
            if (std::find(NewChunksPositions.begin(), NewChunksPositions.end(), ChunkPair.first) == NewChunksPositions.end()) {
                ChunksToUnload.push_back(ChunkPair.first);
            } else {
                NewChunksPositions.erase(std::remove(NewChunksPositions.begin(), NewChunksPositions.end(), ChunkPair.first), NewChunksPositions.end());
            }
        }

        // Unload chunks
        for (const auto& ChunkPos : ChunksToUnload) {
            Chunks.erase(ChunkPos);
        }

        // Load new chunks
        for (const glm::ivec2& ChunkPos : NewChunksPositions) {
            LoadChunk(ChunkPos);
        }
    }
	//TODO unload other chunk
}

glm::ivec2 HC::ChunkManager2D::GetChunkPositionAtPosition(const glm::vec2& Position)
{
	return { std::floor(Position.x / (Chunk2D::TILES_X * Chunk2D::Scale)), 0 };
}

std::vector<glm::ivec2> HC::ChunkManager2D::GetChunksPositionUsingFrustrum(const Camera& camera)
{
    //TODO : Better implementation using camera frustrum

    glm::ivec2 CenteredChunkPos = GetChunkPositionAtPosition(camera.GetPosition());
    return {CenteredChunkPos-glm::ivec2(2,0), CenteredChunkPos-glm::ivec2(1,0), CenteredChunkPos, CenteredChunkPos + glm::ivec2(1,0), CenteredChunkPos + glm::ivec2(2,0)};
}

uint16_t HC::ChunkManager2D::GetTileAtLocation(const glm::vec2 &WorldPosition) {
    const glm::vec2 ChunkPos = GetChunkPositionAtPosition(WorldPosition);
    if (Chunks.find(ChunkPos) != Chunks.end()) {
        glm::vec2 RelativePosition = WorldPosition - glm::vec2 (Chunks[ChunkPos]->position);
        return Chunks[ChunkPos]->GetTileAtLocation(glm::ivec2(RelativePosition / Chunk2D::Scale));
    }
}
