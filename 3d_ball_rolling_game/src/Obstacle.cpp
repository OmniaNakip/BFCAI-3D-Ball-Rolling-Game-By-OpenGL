#include "Obstacle.h"
#include <glad/glad.h>
using namespace std;

Obstacle::Obstacle(glm::vec3 pos, float w, float h, float d)
{
    position = pos;
    width    = w;
    height   = h;
    depth    = d;

    float hw = w / 2.0f;
    float hd = d / 2.0f;

    // Simple box, sitting on Y = 0, height goes up
    float vertices[] = {
        // front
        -hw, 0.0f,  hd,
         hw, 0.0f,  hd,
         hw,    h,  hd,
        -hw,    h,  hd,
        // back
        -hw, 0.0f, -hd,
         hw, 0.0f, -hd,
         hw,    h, -hd,
        -hw,    h, -hd
    };

    unsigned int indices[] = {
        0, 1, 2,  0, 2, 3, // front
        5, 4, 7,  5, 7, 6, // back
        4, 0, 3,  4, 3, 7, // left
        1, 5, 6,  1, 6, 2, // right
        3, 2, 6,  3, 6, 7, // top
        4, 5, 1,  4, 1, 0  // bottom
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // location = 0 -> position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Obstacle::Draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Obstacle::CleanUp()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
