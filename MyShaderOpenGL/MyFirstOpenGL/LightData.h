#pragma once
#include <glm.hpp>


struct LightData
{
    // Luz ambiente 
    glm::vec3 ambientColor = glm::vec3(1.0f);
    float ambientIntensity = 0.1f;

    //directional light
    glm::vec3 sunDirection  = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 sunColor = glm::vec3(1.0f, 0.95f, 0.8f);
    float sunIntensity  = 1.0f;
    float sunActive = 1.0f; // 1 si el sol esta por encima del horizonte, 0 si no

    // directional light a 180 grados
    glm::vec3 moonDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 moonColor = glm::vec3(0.4f, 0.5f, 0.8f);
    float moonIntensity  = 0.4f;
    float moonActive   = 0.0f;

    // spotlight
    glm::vec3 spotPosition  = glm::vec3(0.0f);
    glm::vec3 spotDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 spotColor  = glm::vec3(1.0f, 0.95f, 0.85f);
    float spotIntensity = 3.0f;
    float spotInnerCos = 0.97f; // cos(14 grados) aprox
    float spotOuterCos = 0.92f; // cos(23 grados) aprox
    float spotRange  = 15.0f;
    int spotEnabled = 0;
};
