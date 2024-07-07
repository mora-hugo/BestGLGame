#include <Sprite.h>
#include <vector>
#include <Singleton.h>
#include <ResourceManager.h>



HC::Sprite::Sprite(AABB aabb, const std::string& texturePath) : spriteAABB(aabb) {
    CreateBuffers();
    CreateTexture(texturePath);
    Update();

}

HC::Sprite::Sprite(AABB aabb) : spriteAABB(aabb){
    CreateBuffers();
    Update();
}


void HC::Sprite::Update() {
    glm::vec2 topLeft = spriteAABB.start;
    glm::vec2 bottomRight = spriteAABB.start + glm::vec2{spriteAABB.width, spriteAABB.height};
    glm::vec2 bottomLeft = spriteAABB.start + glm::vec2{0, spriteAABB.height};
    glm::vec2 topRight = spriteAABB.start + glm::vec2{spriteAABB.width, 0};


    std::vector<Vertex> vertices = {
            // positions          // colors           // texture coords
            {glm::vec3{topRight, 0},   {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}}, // top right
            {glm::vec3{bottomRight, 0},   {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},   // bottom right
            {glm::vec3 {bottomLeft, 0},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},   // bottom left
            {glm::vec3 {topLeft,0},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}    // top left
    };

    std::vector<GLuint> indices {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };


    BindBuffers(vertices, indices);


}

