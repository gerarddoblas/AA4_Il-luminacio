#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Cube.h"
#include "ModelObject.h"
#include "DirectionalLight.h"
#include "DayNightCycle.h"
#include "SpotLight.h"

class MainScene : public Scene {
public:
    void OnEnter() override;
    void Update(float dt) override;

private:
    // Luces y modelos que necesito en Update
    DayNightCycle* dayNightCycle = nullptr;
    DirectionalLight* sun = nullptr;
    DirectionalLight* moon = nullptr;
    ModelObject* sunVisual = nullptr;
    ModelObject* moonVisual = nullptr;
    SpotLight* flashlight = nullptr;

    // Ambient
    glm::vec3 ambientColor = glm::vec3(0.9f, 0.85f, 0.6f);
    float ambientIntensity = 0.35f;
};
