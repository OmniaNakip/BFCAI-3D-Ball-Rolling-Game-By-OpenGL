#include "Scene.h"
using namespace std;

Scene::Scene() : ground(20.0f), ball(0.5f, glm::vec3(0.0f, 0.5f, 0.0f))
{
    // Obstacles: position, width, height, depth
    obstacles.push_back(Obstacle(glm::vec3( 3.0f, 0.0f,  2.0f)));
    obstacles.push_back(Obstacle(glm::vec3(-3.0f, 0.0f, -2.0f)));
    obstacles.push_back(Obstacle(glm::vec3( 0.0f, 0.0f, -5.0f), 2.0f, 1.0f, 1.0f));
    obstacles.push_back(Obstacle(glm::vec3(-5.0f, 0.0f,  4.0f)));
    obstacles.push_back(Obstacle(glm::vec3( 5.0f, 0.0f, -3.0f)));
}

void Scene::Draw(unsigned int shaderProgram)
{
    glm::mat4 model;

    glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.3f, 0.6f, 0.3f);
    model = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    ground.Draw();

    glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.9f, 0.2f, 0.2f);
    model = glm::mat4(1.0f);
    model = glm::translate(model, ball.position);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    ball.Draw();

    for (int i = 0; i < obstacles.size(); i++)
    {
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.6f, 0.6f, 0.6f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, obstacles[i].position);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        obstacles[i].Draw();
    }
}

void Scene::CleanUp()
{
    ground.CleanUp();
    ball.CleanUp();

    for (int i = 0; i < obstacles.size(); i++)
        obstacles[i].CleanUp();
}
