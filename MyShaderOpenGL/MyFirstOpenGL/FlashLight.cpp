#include "FlashLight.h"
#include "InputManager.h"

FlashLight::FlashLight() : Light() {}

void FlashLight::Update(float dt)
{
    if (IM->GetKey(GLFW_KEY_F, DOWN))
        enabled = !enabled;
}

float FlashLight::GetInCircle() const { return cos(glm::radians(inCircleAngle)); }
float FlashLight::GetOutCircle() const { return cos(glm::radians(outCircleAngle)); }
