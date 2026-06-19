#include "DayNightCycle.h"
#include <gtc/matrix_transform.hpp>
#include <algorithm>

DayNightCycle::DayNightCycle(DirectionalLight* sun, DirectionalLight* moon)
    : sun(sun), moon(moon)
{
    delete meshRenderer;
    meshRenderer = nullptr;
}

void DayNightCycle::Update(float dt)
{
    
   
}



glm::vec3 DayNightCycle::CalcAmbientColor(float t) const
{   
    return glm::vec3(1.0f);
}

float DayNightCycle::CalcAmbientIntensity(float t) const
{
    //De noche el ambiente es debil (0.05), de dia es visible (0.35)
    float factor = (t + 1.0f) * 0.5f;
    return glm::mix(0.05f, 0.35f, factor);
}
