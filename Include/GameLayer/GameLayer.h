#pragma once

#include "Program.h"

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
        Program program;

    };
};
