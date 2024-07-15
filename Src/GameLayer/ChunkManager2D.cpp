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
	ChunkPtr->position = WorldChunkPosition;
	ChunkPtr->GenerateBlocks();
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

void HC::ChunkManager2D::RebuildChunksIfNecessary()
{
    for (auto& chunkPair : Chunks) {
        if (!chunkPair.second) continue;
        chunkPair.second->RebuildMeshIfNecessary();
    }
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
    //Get tile at world position
    glm::ivec2 ChunkPosition = GetChunkPositionAtPosition(WorldPosition);
    if (Chunks.find(ChunkPosition) == Chunks.end()) {
        return 0;
    }
    glm::ivec2 RelativePosition = (WorldPosition - glm::vec2(Chunks[ChunkPosition]->position)) / Chunk2D::Scale;
    std::cout << "Relative Position : " << RelativePosition.x << " " << RelativePosition.y << std::endl;
    return Chunks[ChunkPosition]->GetTileAtLocation(RelativePosition);
}

void HC::ChunkManager2D::SetTileAtLocation(const glm::vec2 &WorldPosition, uint16_t Tile) {
    glm::ivec2 ChunkPosition = GetChunkPositionAtPosition(WorldPosition);
    if (Chunks.find(ChunkPosition) == Chunks.end()) {
        return;
    }
    glm::ivec2 RelativePosition = (WorldPosition - glm::vec2(Chunks[ChunkPosition]->position)) / Chunk2D::Scale;
    Chunks[ChunkPosition]->SetTileAtLocation(RelativePosition, Tile);
}
