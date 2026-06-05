#include "Light.h"

Light::Light() : GameObject()
{
    // Las luces no necesitan MeshRenderer
    delete meshRenderer;
    meshRenderer = nullptr;
}
