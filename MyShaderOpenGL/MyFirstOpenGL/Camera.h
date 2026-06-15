#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "FlashLight.h"

class Camera : public GameObject {
public:

    glm::vec3 localVectorUp = glm::vec3(0.f, 1.f, 0.f);

    float fFov = 60.0f;
    float fnear = 0.1f;
    float fFar = 100.f;

    float mouseSensitivity = 0.1f;
    float moveSpeed = 3.0f;

    FlashLight* flashlight = nullptr;

    Camera();
    ~Camera();

    void Update(float dt) override;

    glm::vec3 GetRight() const;

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;
};