#include <SpriteRenderer.h>
#include <memory>
#include <ResourceManager.h>

HC::SpriteRenderer::SpriteRenderer(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    std::shared_ptr<ShaderResource> shaderResource = ResourceManager::GetInstance()->Load<ShaderResource>(vertexShaderPath,GL_VERTEX_SHADER);
    std::shared_ptr<ShaderResource> fragmentResource = ResourceManager::GetInstance()->Load<ShaderResource>(fragmentShaderPath,GL_FRAGMENT_SHADER);

    program.AttachShader(shaderResource->GetShader().GetId());
    program.AttachShader(fragmentResource->GetShader().GetId());
    program.Link();

    CompileStatus compileStatus;
    program.GetCompileStatus(compileStatus);
    Assertion(compileStatus.success, std::format("Program Link Error: {0}", compileStatus.infoLog));
    program.Use();
    program.DeleteShader(shaderResource->GetShader().GetId());
    program.DeleteShader(fragmentResource->GetShader().GetId());

    ResourceManager::GetInstance()->Unload(vertexShaderPath);
    ResourceManager::GetInstance()->Unload(fragmentShaderPath);
}

HC::SpriteRenderer::~SpriteRenderer() {

}

void HC::SpriteRenderer::DrawSprite(const Sprite &sprite) const{
    program.Use();
    sprite.Draw();
}
