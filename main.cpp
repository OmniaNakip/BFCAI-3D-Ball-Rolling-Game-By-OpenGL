#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shader.h"
#include "Ball.h"
#include "Scene.h"
#include "camera/Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Camera camera(glm::vec3(0.0f, 3.0f, 5.0f));
float lastX = 400.0f;
float lastY = 300.0f;
bool firstMouse = true;
bool cKeyProcessed = false;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll((float)yoffset);
}

void processInput(GLFWwindow* window, Scene& scene, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera-relative movement directions
    glm::vec3 forward = camera.Front;
    forward.y = 0.0f;
    forward = glm::normalize(forward);
    glm::vec3 right = camera.Right;
    right.y = 0.0f;
    right = glm::normalize(right);

    glm::vec3 moveDir(0.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) moveDir += forward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) moveDir -= forward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) moveDir -= right;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) moveDir += right;

    if (glm::length(moveDir) > 0.0f)
    {
        moveDir = glm::normalize(moveDir);
        scene.ball.velocity += moveDir * scene.ball.moveSpeed * deltaTime;
    }
}

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Ball Game", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "Window created successfully" << std::endl;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "GLAD initialized successfully" << std::endl;

    glEnable(GL_DEPTH_TEST);
    Shader ourShader;
    std::cout << "Shader compiled and linked" << std::endl;
    Scene gameScene;
    std::cout << "Scene initialized. Entering game loop..." << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, gameScene, deltaTime);
        gameScene.ball.Update(deltaTime);

        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !cKeyProcessed)
        {
            camera.ToggleMode();
            cKeyProcessed = true;
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
            cKeyProcessed = false;

        camera.FollowTarget(gameScene.ball.position, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ourShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

        gameScene.Draw(ourShader.ID);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    gameScene.CleanUp();
    return 0;
}
