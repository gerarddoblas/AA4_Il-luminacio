#pragma once
#include "GameObject.h"
#include "DirectionalLight.h"
#include "LightData.h"
#include <glm.hpp>
#include <functional>

// Controla el ciclo dia/noche - orbita el sol y la luna
// y modifica el ambient que se expone a la escena mediante el callback
class DayNightCycle : public GameObject
{
public:
    float cycleDuration = 20.0f; // segundos por ciclo completo
    float orbitRadius   = 8.0f;

    // Callback que la escena puede usar para recibir el ambient calculado
    std::function<void(glm::vec3 color, float intensity)> onAmbientChanged;

    DayNightCycle(DirectionalLight* sun, DirectionalLight* moon);

    void Update(float dt) override;
    void Render(const glm::mat4& view, const glm::mat4& proj, const LightData& lights) override {}

    float GetAngleDeg() const { return angleDeg; }

private:
    DirectionalLight* sun  = nullptr;
    DirectionalLight* moon = nullptr;
    float angleDeg         = 0.0f; // angulo actual de la orbita

    // Calcula la direccion del astro dado su angulo en la orbita
    void ApplyOrbitToLight(DirectionalLight* light, float deg);

    // Interpola el color ambient entre medianoche y mediodia
    glm::vec3 CalcAmbientColor(float t) const;
    float     CalcAmbientIntensity(float t) const;
};
