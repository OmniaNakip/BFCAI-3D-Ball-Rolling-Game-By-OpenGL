#include "Ball.h"
#include <glm/glm.hpp>
#include <cmath>
using namespace std;

Ball::Ball(float r, glm::vec3 startPos)
{
    radius   = r;
    position = startPos;
    velocity = glm::vec3(0.0f);
    moveSpeed = 15.0f;
    friction = 0.95f;

    vector<float>        vertices;
    vector<unsigned int> indices;

    // How smooth the sphere looks (more = smoother but heavier)
    int stacks = 18;
    int slices = 36;

    const float PI = 3.14159265f;

    // Generate sphere vertices using stacks and slices
    for (int i = 0; i <= stacks; i++)
    {
        float phi = PI * i / stacks; // vertical angle

        for (int j = 0; j <= slices; j++)
        {
            float theta = 2.0f * PI * j / slices; // horizontal angle

            float x = radius * sin(phi) * cos(theta);
            float y = radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    // Generate indices
    for (int i = 0; i < stacks; i++)
    {
        for (int j = 0; j < slices; j++)
        {
            int top    = i * (slices + 1) + j;
            int bottom = top + slices + 1;

            indices.push_back(top);
            indices.push_back(bottom);
            indices.push_back(top + 1);

            indices.push_back(top + 1);
            indices.push_back(bottom);
            indices.push_back(bottom + 1);
        }
    }

    indexCount = indices.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // location = 0 -> position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Ball::Update(float deltaTime)
{
    position += velocity * deltaTime;
    velocity *= friction; // Simple damping
}

void Ball::Draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Ball::CleanUp()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
