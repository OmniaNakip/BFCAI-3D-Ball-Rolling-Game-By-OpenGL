#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Obstacle
{
public:
    unsigned int VAO, VBO, EBO;

    glm::vec3 position;
    float     width, height, depth;

    Obstacle(glm::vec3 pos, float w = 1.0f, float h = 1.5f, float d = 1.0f);
    void Draw();
    void CleanUp();
};
