
#include <FirstGameLayer.h>
#include <iostream>
#include "imgui.h"
#include "Model.h"
#include "InputManager.h"
#include "GLFW/glfw3.h"

namespace HC {
    void FirstGameLayer::BeginPlay() {
        GameLayer::BeginPlay();

        InputManager::GetInstance()->ListenKey(GLFW_KEY_W);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_S);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_A);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_D);

    InputManager::GetInstance()->KeyboardEvent.AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&FirstGameLayer::InputCallback, this, 1));
    }

    void FirstGameLayer::Update(float deltaTime) {
        GameLayer::Update(deltaTime);
        cachedDeltaTime = deltaTime;

        sprite.Update();

    }

    void FirstGameLayer::EndPlay() {
        GameLayer::EndPlay();

    }

    void FirstGameLayer::Draw() {
        GameLayer::Draw();

        Renderer.DrawSprite(sprite);


    }
#if REMOVE_IMGUI == 0
    void FirstGameLayer::DrawImGui() {
        GameLayer::DrawImGui();
        ImGui::Begin("Performances");
        ImGui::Text("Frame time: %f", cachedDeltaTime);
        ImGui::Text("FPS: %f", 1.0f / cachedDeltaTime);
        ImGui::End();
    }
#endif
    FirstGameLayer::~FirstGameLayer() {

    }

    FirstGameLayer::FirstGameLayer() {

    }

    void FirstGameLayer::InputCallback(const KeyboardInput& input) {
        if (input.key == GLFW_KEY_W) {
            sprite.spriteAABB.start.y += 1.f * cachedDeltaTime;
        }
        if (input.key == GLFW_KEY_S) {
            sprite.spriteAABB.start.y -= 1.f * cachedDeltaTime;
        }
        if (input.key == GLFW_KEY_A) {
            sprite.spriteAABB.start.x -= 1.f * cachedDeltaTime;
        }
        if (input.key == GLFW_KEY_D) {
            sprite.spriteAABB.start.x += 1.f * cachedDeltaTime;
        }
    }
}
