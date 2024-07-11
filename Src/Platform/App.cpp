#include <App.h>
#include <iostream>
#include <Window.h>
#include <GameLayer.h>
#include "FirstGameLayer.h"
#include "ResourceManager.h"

int HC::App::Run() {
    gameLayer->BeginPlay();
    while (!glfwWindowShouldClose(window->GetGLFWWindow())) {
        glfwPollEvents();
        InputManager::GetInstance()->ProcessInput();
        gameLayer->Update(CalculateDeltaTime());
        gameLayer->Draw();

#if REMOVE_IMGUI == 0
        gameLayer->DrawImGui_Internal();
#endif
        glfwSwapBuffers(window->GetGLFWWindow());
    }
    gameLayer->EndPlay();
    return EXIT_SUCCESS;
}

HC::App::App() {
    auto Config = ResourceManager::GetInstance()->Load<ConfigResource>(RESOURCES_PATH"/Configs/Config.conf");
    glm::ivec2 windowSize {0};
    std::string windowName;
    Assertion(Config && Config->GetValue<int>("window_width", windowSize.x) && Config->GetValue<int>("window_height", windowSize.y) && Config->GetValue("window_name", windowName), "Failed to load window size from config");
    window = std::make_unique<Window>(windowSize.x, windowSize.y, "Hello World");
    gameLayer = std::make_unique<FirstGameLayer>(this);

    InputManager::GetInstance()->Init(window.get());
}




HC::App::~App() {

}

float HC::App::CalculateDeltaTime() {
    float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
    previousTime = currentTime;
    currentTime = std::chrono::high_resolution_clock::now();
    return dt;
}

glm::vec2 HC::App::GetWindowSize() const {
    return window->GetWindowSize();
}




