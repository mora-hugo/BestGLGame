#pragma once
#include <glm/vec2.hpp>
#include <AABB.h>
#include <glad/glad.h>
#include <vector>

namespace HC {

    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoord;
    };

    struct Sprite {
        friend class SpriteRenderer;

        AABB spriteAABB;
        Sprite(AABB aabb);
        void Update();

    protected:
        void Draw() const;


    private:
        /* Buffers */
        void CreateBuffers();
        void BindBuffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);


    private:
        GLsizei vertexCount = 0;
        GLsizei indexCount = 0;
        bool bUsingIndexBuffer = false;

        GLuint VBO, VAO, EBO;
    };

}
