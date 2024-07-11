#pragma once

#include "GameLayer.h"
#include "InputManager.h"
#include "TileRenderer.h"
#include "Camera.h"
#include <memory>

namespace HC {
    class Model;
    class FirstGameLayer : public GameLayer {
    public:
        FirstGameLayer(App * app);
        ~FirstGameLayer() override;
        void BeginPlay() override;
        void Update(float deltaTime) override;
        void Draw() override;
        void EndPlay() override;

#if REMOVE_IMGUI == 0
        void DrawImGui() override;
#endif

        void InputCallback(const KeyboardInput& input);
    private:
        float cachedDeltaTime = 0.0f;
        Sprite sprite {Rect(glm::vec2(0.0f, 0.0f), 0.5, 0.5), RESOURCES_PATH"/Textures/wall.jpg"};
        float Zoom = 55.0f;
        Camera camera;
        std::vector<std::unique_ptr<TilesContainer>> containers;
    };
};
