#pragma once

#include "GameLayer.h"
#include <memory>

namespace HC {
    class Model;
    class FirstGameLayer : public GameLayer {
    public:
        FirstGameLayer();
        ~FirstGameLayer() override;
        void BeginPlay() override;
        void Update(float deltaTime) override;
        void Draw() override;
        void EndPlay() override;

#if REMOVE_IMGUI == 0
        void DrawImGui() override;
#endif
    private:
        float cachedDeltaTime = 0.0f;
        std::unique_ptr<Model> model;


    };
};
