#include "DirectionalLight.h"
#include <gtc/matrix_transform.hpp>

DirectionalLight::DirectionalLight() : Light() {}

glm::vec3 DirectionalLight::GetDirection() const
{
    // forward
    float yaw   = transform->rotation.x;
    float pitch = transform->rotation.y;

    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(dir);
}
