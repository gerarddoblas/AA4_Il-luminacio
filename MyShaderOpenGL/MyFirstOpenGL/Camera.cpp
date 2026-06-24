#include "Camera.h"
#include "InputManager.h"

Camera::Camera() : GameObject()
{
    transform->position = glm::vec3(0.0f, 0.5f, 4.0f);
    transform->rotation.x = -90.0f;
    flashlight = new FlashLight();
    LM->AddFlashLight(flashlight);
}

Camera::~Camera()
{
    if (flashlight)
    {
        delete flashlight;
        flashlight = nullptr;
    }
}

void Camera::Update(float dt)
{
    float deltaX = (float)IM->GetMouseDeltaX() * mouseSensitivity;
    float deltaY = (float)IM->GetMouseDeltaY() * mouseSensitivity;

    transform->rotation.x += deltaX;
    transform->rotation.y -= deltaY;
    transform->rotation.y = glm::clamp(transform->rotation.y, -89.0f, 89.0f);

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

    if (flashlight)
    {
        flashlight->Update(dt);
        flashlight->GetTransform()->position = transform->position;
        flashlight->GetTransform()->rotation = glm::vec3(transform->rotation.x, transform->rotation.y, 0.0f);
    }
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