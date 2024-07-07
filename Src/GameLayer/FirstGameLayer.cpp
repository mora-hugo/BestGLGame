
#include <FirstGameLayer.h>
#include <imgui.h>
#include <InputManager.h>
#include <GLFW/glfw3.h>
#include <ResourceManager.h>
#include <glm/matrix.hpp>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace HC {
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
        tilesContainer.GenerateBlocks();
        tilesContainer.GenerateMesh();

        InputManager::GetInstance()->KeyboardEvent.AddListener(this, HC_BIND_MEMBER_FUNCTION_ARGS(&FirstGameLayer::InputCallback, this, 1));

        tileRenderer.GetProgram().SetUniformMat4("model", glm::mat4{1.0f});
        SpriteRenderer.GetProgram().SetUniformMat4("model", glm::mat4{1.0f});

        auto Conf = ResourceManager::GetInstance()->Load<ConfigResource>(RESOURCES_PATH"/Configs/Config.conf");
        int key;
        Conf->GetValue<int>("test", key);
        std::cout << key << std::endl;


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


        tileRenderer.GetProgram().SetUniformMat4("view", glm::lookAt(glm::vec3(cameraPosition.x,cameraPosition.y, 30), glm::vec3(cameraPosition.x,cameraPosition.y, 0), glm::vec3(0.0f, 1.0f, 0.0f)));
        SpriteRenderer.GetProgram().SetUniformMat4("view", glm::lookAt(glm::vec3(cameraPosition.x,cameraPosition.y, 30), glm::vec3(cameraPosition.x,cameraPosition.y, 0), glm::vec3(0.0f, 1.0f, 0.0f)));
        tileRenderer.GetProgram().SetUniformMat4("projection", glm::ortho(-2.0f*Zoom, +2.0f*Zoom, -1.5f*Zoom, +1.5f*Zoom, 0.1f, 100.0f));
        SpriteRenderer.GetProgram().SetUniformMat4("projection", glm::ortho(-2.0f*Zoom, +2.0f*Zoom, -1.5f*Zoom, +1.5f*Zoom, 0.1f, 100.0f));

        SpriteRenderer.DrawSprite(sprite);

        tileRenderer.DrawTiles(tilesContainer);







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
        if(input.key == GLFW_KEY_PAGE_DOWN && input.action == KeyboardAction::VP_KEY_REPEAT) {
            Zoom -= 1.f * cachedDeltaTime;
        }
        if(input.key == GLFW_KEY_PAGE_UP && input.action == KeyboardAction::VP_KEY_REPEAT) {
            Zoom += 1.f * cachedDeltaTime;
        }
        if(input.key == GLFW_KEY_LEFT && input.action == KeyboardAction::VP_KEY_REPEAT) {
            cameraPosition.x -= 1.f * cachedDeltaTime;
        }
        if(input.key == GLFW_KEY_RIGHT && input.action == KeyboardAction::VP_KEY_REPEAT) {
            cameraPosition.x += 1.f * cachedDeltaTime;
        }
        if(input.key == GLFW_KEY_UP && input.action == KeyboardAction::VP_KEY_REPEAT) {
            cameraPosition.y += 1.f * cachedDeltaTime;
        }
        if(input.key == GLFW_KEY_DOWN && input.action == KeyboardAction::VP_KEY_REPEAT) {
            cameraPosition.y -= 1.f * cachedDeltaTime;
        }
    }
}
