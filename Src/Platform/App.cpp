#include <App.h>
#include <iostream>
#include <Window.h>
#include <GameLayer.h>
#include "FirstGameLayer.h"

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
    window = std::make_unique<Window>(800, 600, "Hello World");
    gameLayer = std::make_unique<FirstGameLayer>();

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



