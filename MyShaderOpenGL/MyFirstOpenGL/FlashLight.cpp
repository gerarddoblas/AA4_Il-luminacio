#include "FlashLight.h"
#include "InputManager.h"

FlashLight::FlashLight() : Light() {}

void FlashLight::Update(float dt)
{
    if (IM->GetKey(GLFW_KEY_F, DOWN))
        enabled = !enabled;
}


float FlashLight::GetInnerCos() const { return cos(glm::radians(innerCutoffDeg)); }
float FlashLight::GetExterCos() const { return cos(glm::radians(exterCutoffDeg)); }
