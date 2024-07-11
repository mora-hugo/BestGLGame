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
	for (const glm::ivec2& ChunkPos : ChunksPositions) {
		LoadChunk(ChunkPos);
	}
	//TODO unload other chunk
}

glm::ivec2 HC::ChunkManager2D::GetChunkPositionAtPosition(const glm::vec2& Position)
{
	return { std::floor(Position.x / Chunk2D::TILES_X * Chunk2D::Scale), 0 };
}

std::vector<glm::ivec2> HC::ChunkManager2D::GetChunksPositionUsingFrustrum(const Camera& camera)
{
	std::vector<glm::ivec2> NewChunks;
	const glm::uvec2 WindowSize = Window::GetWindowSize();
	// Calculate the "size" of the visible screen using the Camera's Zoom parameter
	const glm::ivec2 Size = WindowSize * (unsigned int)(1 / camera.GetZoom());

	// This is the max number of chunk that need to be rendered and loaded
	int MaxViewportChunkSize = (std::floor((Size.x / 2) / Chunk2D::TILES_X * Chunk2D::Scale)) + 1;
	for (int i = -MaxViewportChunkSize; i <= MaxViewportChunkSize; i++) {
		NewChunks.push_back({ i, 0});
	}

	return NewChunks;
}

