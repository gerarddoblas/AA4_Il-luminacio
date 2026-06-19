#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Cube.h"
#include "ModelObject.h"
#include "DirectionalLight.h"
#include "LightManager.h"

class MainScene : public Scene {
public:
    void OnEnter() override;
    void Update(float dt) override;

private:
    const int MAX_DIRECTIONALS = 2;
    // Luces y modelos que necesito en Update
    DirectionalLight* sun = nullptr;
    DirectionalLight* moon = nullptr;
    ModelObject* sunVisual = nullptr;
    ModelObject* moonVisual = nullptr;
    // Ambient
    glm::vec3 ambientColor = glm::vec3(0.9f, 0.85f, 0.6f);
    float ambientIntensity = 0.35f;

    //Variables
    float timeDayNight = 0.f;
    float cycleDuration = 10.0f;
    float circleDegrees = 360.0f;
    float orbitRadius = 8.0f;
    float timeWithDegrees = 0.f;

    void UpdateDayNight(float dt);
    void OrbitAroundWorld(DirectionalLight* light, float deg);
    

};
