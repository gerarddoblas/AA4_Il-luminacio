#pragma once
#include "Light.h"

class FlashLight : public Light
{
public:
    const float innerCutoffDeg = 14.0f; //interior 
    const float exterCutoffDeg = 23.0f; //exterior
    const float range = 15.0f;
    bool enabled = false;

    FlashLight();

    void Update(float dt) override;

    float GetInnerCos() const;
    float GetExterCos() const;
};
