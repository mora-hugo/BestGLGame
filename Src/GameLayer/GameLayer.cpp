
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
