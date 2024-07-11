#include <Renderer.h>
#include <memory>
#include <ResourceManager.h>
HC::Renderer::Renderer(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    std::shared_ptr<ShaderResource> shaderResource = ResourceManager::GetInstance()->Load<ShaderResource>(vertexShaderPath,GL_VERTEX_SHADER);
    std::shared_ptr<ShaderResource> fragmentResource = ResourceManager::GetInstance()->Load<ShaderResource>(fragmentShaderPath,GL_FRAGMENT_SHADER);

    program.AttachShader(shaderResource->GetShader().GetId());
    program.AttachShader(fragmentResource->GetShader().GetId());
    program.Link();

    CompileStatus compileStatus;
    program.GetCompileStatus(compileStatus);
    Assertion(compileStatus.success, "Program Link Error" + compileStatus.infoLog);
    program.DeleteShader(shaderResource->GetShader().GetId());
    program.DeleteShader(fragmentResource->GetShader().GetId());
    ResourceManager::GetInstance()->Unload(vertexShaderPath);
    ResourceManager::GetInstance()->Unload(fragmentShaderPath);
}

HC::Renderer::~Renderer() {

}

void HC::Renderer::Draw(const IDrawable& renderable) const{
    program.Use();
    renderable.Draw();
}

void HC::Renderer::ClearScreen(const glm::vec4 color) {

    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

