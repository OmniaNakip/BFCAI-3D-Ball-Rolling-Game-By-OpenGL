#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Ground.h"
#include "Ball.h"
#include "Obstacle.h"
using namespace std;

class Scene
{
public:
    Ground            ground;
    Ball              ball;
    vector<Obstacle>  obstacles;

    Scene();
    void Draw(unsigned int shaderProgram);
    void CleanUp();
};
