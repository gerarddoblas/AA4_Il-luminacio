#pragma once
#include "GameObject.h"
#include <glm.hpp>

// Clase base para todas las luces - es un GameObject pero no tiene mesh
class Light : public GameObject
{
public:
    glm::vec3 color     = glm::vec3(1.0f);
    float     intensity = 1.0f;

    Light();

    // Las luces no renderizan nada por defecto
    void Render(const glm::mat4& view, const glm::mat4& proj, const struct LightData& lights) override {}
};
