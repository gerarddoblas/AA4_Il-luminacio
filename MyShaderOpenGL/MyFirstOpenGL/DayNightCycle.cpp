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
    
    float degreesPerSecond = 360.0f / cycleDuration;
    angleDeg += degreesPerSecond * dt;
    if (angleDeg >= 360.0f) angleDeg -= 360.0f;

    //180 grados entre si
    ApplyOrbitToLight(sun,  angleDeg);
    ApplyOrbitToLight(moon, angleDeg + 180.0f);

    // angulo 90 = sol
    float t = sin(glm::radians(angleDeg));

    // Calculamos el ambient de este momento y avisamos a quien escuche
    if (onAmbientChanged)
    {
        onAmbientChanged(CalcAmbientColor(t), CalcAmbientIntensity(t));
    }
}

void DayNightCycle::ApplyOrbitToLight(DirectionalLight* light, float deg)
{
    // Z fijo
    
    float rad = glm::radians(deg);
    glm::vec3 pos = glm::vec3(sin(rad) * orbitRadius, cos(rad) * orbitRadius, 0.0f);
    light->GetTransform()->position = pos;

    // direccion luz
    glm::vec3 dir = glm::normalize(-pos);

    // Convertimos la direccion a yaw/pitch para que GetDirection() devuelva lo correcto
    // pitch = asin(dir.y),  yaw = atan2(dir.z, dir.x)
    //IA
    float pitch = glm::degrees(asin(dir.y));
    float yaw = glm::degrees(atan2(dir.z, dir.x));
    light->GetTransform()->rotation = glm::vec3(yaw, pitch, 0.0f);

    // solo ilumina si Y positiva
    float sunHeight = pos.y;
    light->isVisible = (sunHeight > 0.0f);
}

glm::vec3 DayNightCycle::CalcAmbientColor(float t) const
{
    
    // t: -1 = medianoche, 0 = amanecer/atardecer, 1 = mediodia
    glm::vec3 night = glm::vec3(0.05f, 0.05f, 0.15f);
    glm::vec3 day   = glm::vec3(0.9f,  0.85f, 0.6f);
    float factor = (t + 1.0f) * 0.5f;
    return glm::mix(night, day, factor);
}

float DayNightCycle::CalcAmbientIntensity(float t) const
{
    // De noche el ambiente es debil (0.05), de dia es visible (0.35)
    float factor = (t + 1.0f) * 0.5f;
    return glm::mix(0.05f, 0.35f, factor);
}
