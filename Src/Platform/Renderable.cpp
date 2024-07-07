#include <Renderable.h>
#include <vector>
#include <Singleton.h>
#include <ResourceManager.h>

void HC::Renderable::Draw() const {

    glBindVertexArray(VAO);
    if(HasTexture())
        BindTexture();
    if(bUsingIndexBuffer) {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }




}

void HC::Renderable::CreateBuffers() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}


void HC::Renderable::BindBuffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices) {

    bUsingIndexBuffer = !indices.empty();
    vertexCount = vertices.size();
    indexCount = indices.size();

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




void HC::Renderable::CreateTexture(const std::string &texturePath) {
    auto textureResource = ResourceManager::GetInstance()->Load<TextureResource>(texturePath);

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    /* set the texture wrapping/filtering options (on the currently bound texture object) */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (textureResource->data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureResource->width, textureResource->height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, textureResource->data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

}

void HC::Renderable::BindTexture() const {

    glBindTexture(GL_TEXTURE_2D, texture);
}
