#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
using namespace std;

class Ball
{
public:
    unsigned int VAO, VBO, EBO;
    int indexCount;

    float radius;

    // Starting position (Member 4 reads this to move the ball)
    glm::vec3 position;

    Ball(float radius = 0.5f, glm::vec3 startPos = glm::vec3(0.0f, 0.5f, 0.0f));
    void Draw();
    void CleanUp();
};
