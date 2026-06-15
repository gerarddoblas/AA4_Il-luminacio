#pragma once
#include "Light.h"

class FlashLight : public Light
{
public:
    float inCircleAngle = 10.0f; //interior
    float outCircleAngle = 15.0f; //exterior
    const float range = 15.0f;
    bool enabled = false;

    FlashLight();

    void Update(float dt) override;

    float GetInCircle() const;
    float GetOutCircle() const;
};
