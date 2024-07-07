#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <string>

namespace HC {

    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoord;
    };

    class Renderable {
        protected:
            void Draw() const;

            /* Buffers */
            void CreateBuffers();

            void BindBuffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);

            /* Textures */

            void CreateTexture(const std::string &texturePath);

            void BindTexture() const;

            bool HasTexture() const { return texture != 0; }

        private:
            GLsizei vertexCount = 0;
            GLsizei indexCount = 0;
            bool bUsingIndexBuffer = false;

            GLuint VBO, VAO, EBO, texture = 0;
        };
}
