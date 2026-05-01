#pragma once
#include <glm/glm.hpp>

enum class CameraMode
{
    FPS,
    THIRD_PERSON
};

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    CameraMode Mode;

    float FollowDistance;
    float FollowHeight;
    float SmoothSpeed;

    Camera(glm::vec3 position = glm::vec3(0.0f, 1.0f, 5.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f,
           float pitch = -20.0f);

    glm::mat4 GetViewMatrix();
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void FollowTarget(glm::vec3 targetPos, float deltaTime);
    void ToggleMode();

private:
    void UpdateCameraVectors();
};
