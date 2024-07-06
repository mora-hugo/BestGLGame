
#include <FirstGameLayer.h>
#include "imgui.h"
#include "Model.h"

namespace HC {
    void FirstGameLayer::BeginPlay() {
        GameLayer::BeginPlay();
        std::vector<Vertex> vertices = {
                // positions          // colors           // texture coords
                {{0.5f,  0.5f, 0.0f},   {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}}, // top right
                {{0.5f, -0.5f, 0.0f},   {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},   // bottom right
                {{-0.5f, -0.5f, 0.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},   // bottom left
                 {{-0.5f,  0.5f, 0.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}    // top left
        };
        std::vector<GLuint> indices {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
        };
        model = std::make_unique<Model>(vertices, indices);


    }

    void FirstGameLayer::Update(float deltaTime) {
        GameLayer::Update(deltaTime);
        cachedDeltaTime = deltaTime;

    }

    void FirstGameLayer::EndPlay() {
        GameLayer::EndPlay();

    }

    void FirstGameLayer::Draw() {
        GameLayer::Draw();
        model->Draw();
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
}
