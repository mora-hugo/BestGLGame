
#include <FirstGameLayer.h>
#include <imgui.h>
#include <InputManager.h>
#include <GLFW/glfw3.h>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <App.h>
#include <iostream>

namespace HC {
    FirstGameLayer::FirstGameLayer(App *app) : GameLayer(app) {

    }
    void FirstGameLayer::BeginPlay() {


        GameLayer::BeginPlay();

        InputManager::GetInstance()->ListenKey(GLFW_KEY_W);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_S);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_A);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_D);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_PAGE_DOWN);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_PAGE_UP);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_LEFT);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_RIGHT);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_UP);
        InputManager::GetInstance()->ListenKey(GLFW_KEY_DOWN);


        InputManager::GetInstance()->KeyboardEvent.AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&FirstGameLayer::InputKeyboardCallback, this, 1));
        InputManager::GetInstance()->MouseEvent.AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&FirstGameLayer::InputMouseCallback, this, 1));



        tileRenderer.GetProgram().SetUniformMat4("model", glm::mat4{1.0f});
        SpriteRenderer.GetProgram().SetUniformMat4("model", glm::mat4{1.0f});
        ChunkManager.LoadChunks({ { -1,0}, { 1,0} });
    }

    void FirstGameLayer::Update(float deltaTime) {
        GameLayer::Update(deltaTime);
        cachedDeltaTime = deltaTime;

        sprite.Update();
        ChunkManager.RebuildChunksIfNecessary();

        tileRenderer.GetProgram().SetUniformMat4("view", camera.GetViewMatrix());
        SpriteRenderer.GetProgram().SetUniformMat4("view", camera.GetViewMatrix());
        tileRenderer.GetProgram().SetUniformMat4("projection", camera.GetProjectionMatrix());
        SpriteRenderer.GetProgram().SetUniformMat4("projection", camera.GetProjectionMatrix());
        camera.SetPosition(sprite.spriteAABB.start + (glm::vec2(sprite.spriteAABB.width, sprite.spriteAABB.height) / 2.f));
        ChunkManager.LoadChunks(ChunkManager2D::GetChunksPositionUsingFrustrum(camera), true);

    }

    void FirstGameLayer::EndPlay() {
        GameLayer::EndPlay();

    }

    void FirstGameLayer::Draw() {

        GameLayer::Draw();
        tileRenderer.Draw(ChunkManager);
        SpriteRenderer.Draw(sprite);

    }
#if REMOVE_IMGUI == 0
    void FirstGameLayer::DrawImGui() {
        GameLayer::DrawImGui();
        ImGui::Begin("Performances");
        ImGui::Text("Frame time (ms): %f", cachedDeltaTime);
        ImGui::Text("FPS: %f", 1.0f / cachedDeltaTime);
        ImGui::End();
    }
#endif
    FirstGameLayer::~FirstGameLayer() {

    }


    void FirstGameLayer::InputKeyboardCallback(const KeyboardInput& input) {
        if (input.key == GLFW_KEY_W) {
            sprite.spriteAABB.start.y += 5.f * cachedDeltaTime;
        }
        if (input.key == GLFW_KEY_S) {
            sprite.spriteAABB.start.y -= 5.f * cachedDeltaTime;
        }
        if (input.key == GLFW_KEY_A) {
            sprite.spriteAABB.start.x -= 5.f * cachedDeltaTime;
        }
        if (input.key == GLFW_KEY_D) {
            sprite.spriteAABB.start.x += 5.f * cachedDeltaTime;
        }
        if(input.key == GLFW_KEY_PAGE_DOWN && input.action == KeyboardAction::VP_KEY_REPEAT) {
            camera.SetZoom(camera.GetZoom() - (1.f * cachedDeltaTime * 15.f));
        }
        if(input.key == GLFW_KEY_PAGE_UP && input.action == KeyboardAction::VP_KEY_REPEAT) {
            camera.SetZoom(camera.GetZoom() + (1.f * cachedDeltaTime * 15.f));
        }
        if(input.key == GLFW_KEY_LEFT && input.action == KeyboardAction::VP_KEY_REPEAT) {
            camera.Move(glm::vec2(-1,0) * 3.f * cachedDeltaTime);
        }
        if(input.key == GLFW_KEY_RIGHT && input.action == KeyboardAction::VP_KEY_REPEAT) {
            camera.Move(glm::vec2(+1,0) *3.f * cachedDeltaTime);
        }
        if(input.key == GLFW_KEY_UP && input.action == KeyboardAction::VP_KEY_REPEAT) {
            camera.Move(glm::vec2(0,1) *3.f * cachedDeltaTime);
        }
        if(input.key == GLFW_KEY_DOWN && input.action == KeyboardAction::VP_KEY_REPEAT) {
            camera.Move(glm::vec2(0,-1) *3.f * cachedDeltaTime);
        }
    }

    void FirstGameLayer::InputMouseCallback(const MouseInput &input) {
        if(input.action == MouseAction::VP_MOUSE_PRESSED && input.key == GLFW_MOUSE_BUTTON_LEFT) {
            ChunkManager.SetTileAtLocation(camera.ScreenToWorld(input.position), Tile::DIRT);
        }
        else if(input.action == MouseAction::VP_MOUSE_PRESSED && input.key == GLFW_MOUSE_BUTTON_RIGHT) {
            ChunkManager.SetTileAtLocation(camera.ScreenToWorld(input.position), Tile::AIR);
        }
    }


}
