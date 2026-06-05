#include "SpotLight.h"
#include <gtc/matrix_transform.hpp>

SpotLight::SpotLight() : Light() {}

glm::vec3 SpotLight::GetDirection() const
{
    float yaw   = transform->rotation.x;
    float pitch = transform->rotation.y;

    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(dir);
}

float SpotLight::GetInnerCos() const { return cos(glm::radians(innerCutoffDeg)); }
float SpotLight::GetOuterCos() const { return cos(glm::radians(outerCutoffDeg)); }
