#include "Camera.h"
#include "InputManager.h"

Camera::Camera() : GameObject()
{
    transform->position = glm::vec3(0.0f, 0.5f, 4.0f);
}

void Camera::Update(float dt)
{
    float deltaX = (float)IM->GetMouseDeltaX() * mouseSensitivity;
    float deltaY = (float)IM->GetMouseDeltaY() * mouseSensitivity;

    yaw += deltaX;
    pitch -= deltaY;
    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    glm::vec3 forward = GetForward();
    glm::vec3 right = GetRight();

    if (IM->GetKey(GLFW_KEY_W, HOLD) || IM->GetKey(GLFW_KEY_W, DOWN))
        transform->position += forward * moveSpeed * dt;

    if (IM->GetKey(GLFW_KEY_S, HOLD) || IM->GetKey(GLFW_KEY_S, DOWN))
        transform->position -= forward * moveSpeed * dt;

    if (IM->GetKey(GLFW_KEY_D, HOLD) || IM->GetKey(GLFW_KEY_D, DOWN))
        transform->position += right * moveSpeed * dt;

    if (IM->GetKey(GLFW_KEY_A, HOLD) || IM->GetKey(GLFW_KEY_A, DOWN))
        transform->position -= right * moveSpeed * dt;
}

glm::vec3 Camera::GetForward() const
{
    glm::vec3 forward;
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(forward);
}

glm::vec3 Camera::GetRight() const
{
    return glm::normalize(glm::cross(GetForward(), localVectorUp));
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(
        transform->position,
        transform->position + GetForward(),
        localVectorUp
    );
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(glm::radians(fFov), aspectRatio, fnear, fFar);
}