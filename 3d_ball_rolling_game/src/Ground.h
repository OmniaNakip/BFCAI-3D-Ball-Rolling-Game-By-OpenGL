#pragma once
#include <glad/glad.h>

class Ground
{
public:
    unsigned int VAO, VBO, EBO;

    Ground(float size = 20.0f);
    void Draw();
    void CleanUp();
};
