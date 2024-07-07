
#include <GameLayer.h>
#include <iostream>
#include "glad/glad.h"
#include "Window.h"
namespace HC {
    void GameLayer::BeginPlay() {

    }

    void GameLayer::Update(float deltaTime) {

    }

    void GameLayer::EndPlay() {

    }

    void GameLayer::Draw() {
        Renderer::ClearScreen(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
    }
#if REMOVE_IMGUI == 0
    void GameLayer::DrawImGui() {

    }

    void GameLayer::DrawImGui_Internal() {
        Window::ImGUIFrameBegin();
        DrawImGui();
        Window::ImGUIRender();
    }


#endif
}
