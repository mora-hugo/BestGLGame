
#include <GameLayer.h>
#include <iostream>
#include "glad/glad.h"
#include "Window.h"
#include "imgui.h"
#include "ResourceManager.h"
#include <Assertion.h>
#include <format>
namespace HC {
    void GameLayer::BeginPlay() {
        std::shared_ptr<ShaderResource> shaderResource = ResourceManager::GetInstance()->Load<ShaderResource>(RESOURCES_PATH"/Shaders/vertex.glsl",GL_VERTEX_SHADER);
        std::shared_ptr<ShaderResource> fragmentResource = ResourceManager::GetInstance()->Load<ShaderResource>(RESOURCES_PATH"/Shaders/fragment.glsl",GL_FRAGMENT_SHADER);

        program.AttachShader(shaderResource->GetShader().GetId());
        program.AttachShader(fragmentResource->GetShader().GetId());
        program.Link();
        CompileStatus compileStatus;

        program.GetCompileStatus(compileStatus);
        Assertion(compileStatus.success, std::format("Program Link Error: {0}", compileStatus.infoLog));

        program.Use();
        program.DeleteShader(shaderResource->GetShader().GetId());
        program.DeleteShader(fragmentResource->GetShader().GetId());
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
