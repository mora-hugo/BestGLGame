#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"
#include "Chunk2D.h"
#include "Camera.h"
#include <vector>

namespace HC {

	struct IVec2Cmp
	{
		bool operator()(const glm::ivec2& lhs, const glm::ivec2	& rhs) const
		{
			return lhs.x < rhs.x && lhs.y < rhs.y; 
		}
	};
	class ChunkManager2D : public IDrawable {

		void Draw() const override;
	public:
		void LoadChunk(const glm::ivec2& ChunkPosition);
		void LoadChunks(const std::vector<glm::ivec2>& ChunksPositions, bool AutoUnloadOtherChunks = false);
		
		static glm::ivec2 GetChunkPositionAtPosition(const glm::vec2& Position);
		static std::vector<glm::ivec2> GetChunksPositionUsingFrustrum(const Camera& Camera);
		std::map < glm::ivec2, std::unique_ptr<Chunk2D>, IVec2Cmp> Chunks;
	};

}
