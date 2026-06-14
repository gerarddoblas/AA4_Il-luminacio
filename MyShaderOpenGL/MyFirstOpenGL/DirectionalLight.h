#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
    DirectionalLight();

    void Update(float dt) override {}
};
