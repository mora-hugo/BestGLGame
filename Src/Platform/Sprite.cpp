#include <Sprite.h>
#include <vector>

void HC::Sprite::Draw() const {
    glBindVertexArray(VAO);

    if(bUsingIndexBuffer)
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void HC::Sprite::CreateBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}


HC::Sprite::Sprite(AABB aabb) : spriteAABB(aabb) {
    CreateBuffers();

    Update();

}

void HC::Sprite::BindBuffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices) {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint) , indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
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

    bUsingIndexBuffer = !indices.empty();
    vertexCount = vertices.size();
    indexCount = indices.size();


    BindBuffers(vertices, indices);
}
