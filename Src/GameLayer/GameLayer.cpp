
#include <GameLayer.h>
#include "Window/GLFWWindow.h"
#include <App.h>
#include "Renderer.h"
#include <Interface.h>
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
        auto* imGUIInterface = Interface::GetInterface<IImGUIWindow>(app->GetWindow());
        if(!imGUIInterface) return;

        imGUIInterface->ImGUIFrameBegin();
        DrawImGui();
        imGUIInterface->ImGUIRender();

    }
#endif  
    GameLayer::GameLayer(struct App* appContext) : app(appContext) {

    }

    glm::vec2 GameLayer::GetWindowSize() const {
        return app->GetWindowSize();
    }



}
