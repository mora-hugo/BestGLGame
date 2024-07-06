#pragma once


#include "SpriteRenderer.h"

namespace HC {
    class GameLayer {
    public:
        GameLayer() = default;
        virtual ~GameLayer() = default;

        GameLayer(const GameLayer&) = delete;


        GameLayer& operator=(const GameLayer&) = delete;

        virtual void BeginPlay();
        virtual void Update(float deltaTime);
        virtual void Draw();
        virtual void EndPlay();

#if REMOVE_IMGUI == 0
        void DrawImGui_Internal();

        virtual void DrawImGui();
#endif

    protected:
        SpriteRenderer Renderer { RESOURCES_PATH"/Shaders/vertex.glsl", RESOURCES_PATH"/Shaders/fragment.glsl" };

    };
};
