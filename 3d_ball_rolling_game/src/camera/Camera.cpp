#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(2.5f),
      MouseSensitivity(0.1f),
      Zoom(45.0f),
      Mode(CameraMode::THIRD_PERSON),
      FollowDistance(5.0f),
      FollowHeight(3.0f),
      SmoothSpeed(5.0f)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    if (Mode == CameraMode::THIRD_PERSON)
    {
        return glm::lookAt(Position, Position + Front, Up);
    }
    else
    {
        return glm::lookAt(Position, Position + Front, Up);
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 90.0f)
        Zoom = 90.0f;

    if (Mode == CameraMode::THIRD_PERSON)
    {
        FollowDistance -= yoffset * 0.5f;
        if (FollowDistance < 2.0f)
            FollowDistance = 2.0f;
        if (FollowDistance > 20.0f)
            FollowDistance = 20.0f;
    }
}

void Camera::FollowTarget(glm::vec3 targetPos, float deltaTime)
{
    if (Mode == CameraMode::THIRD_PERSON)
    {
        float horizontalDist = FollowDistance * cos(glm::radians(Pitch));
        float verticalDist = FollowDistance * sin(glm::radians(-Pitch));

        float offsetX = horizontalDist * sin(glm::radians(-Yaw));
        float offsetZ = horizontalDist * cos(glm::radians(-Yaw));

        glm::vec3 desiredPos;
        desiredPos.x = targetPos.x + offsetX;
        desiredPos.y = targetPos.y + verticalDist + FollowHeight * 0.3f;
        desiredPos.z = targetPos.z + offsetZ;

        if (desiredPos.y < 0.5f)
            desiredPos.y = 0.5f;

        float t = 1.0f - std::exp(-SmoothSpeed * deltaTime);
        Position = glm::mix(Position, desiredPos, t);
    }
    else
    {
        glm::vec3 desiredPos = targetPos;
        desiredPos.y += FollowHeight * 0.5f;
        Position = desiredPos;
    }
}

void Camera::ToggleMode()
{
    if (Mode == CameraMode::THIRD_PERSON)
        Mode = CameraMode::FPS;
    else
        Mode = CameraMode::THIRD_PERSON;
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
