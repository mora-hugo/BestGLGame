#pragma once


#include "SpriteRenderer.h"
#include "TileRenderer.h"

namespace HC {
    class GameLayer {
    public:
        GameLayer(class App* appContext);
        virtual ~GameLayer() = default;

        GameLayer(const GameLayer&) = delete;


        GameLayer& operator=(const GameLayer&) = delete;

        virtual void BeginPlay();
        virtual void Update(float deltaTime);
        virtual void Draw();
        virtual void EndPlay();

        glm::vec2 GetWindowSize() const;

#if REMOVE_IMGUI == 0
        void DrawImGui_Internal();

        virtual void DrawImGui();
#endif

    protected:
        TileRenderer tileRenderer  { RESOURCES_PATH"/Shaders/vertex.glsl", RESOURCES_PATH"/Shaders/fragment.glsl" };
        SpriteRenderer SpriteRenderer { RESOURCES_PATH"/Shaders/vertex.glsl", RESOURCES_PATH"/Shaders/fragment.glsl" };

    private:
        class App* app;


    };
};
