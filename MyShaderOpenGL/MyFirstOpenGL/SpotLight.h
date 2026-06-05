#pragma once
#include "Light.h"

class SpotLight : public Light
{
public:
    float innerCutoffDeg = 14.0f; //interior 
    float outerCutoffDeg = 23.0f; //exterior
    float range          = 15.0f;
    bool  enabled        = false;

    SpotLight();

    void Update(float dt) override {}

    glm::vec3 GetDirection() const;
    glm::vec3 GetPosition()  const { return transform->position; }

    float GetInnerCos() const;
    float GetOuterCos() const;
};
