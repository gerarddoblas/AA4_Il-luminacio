#include "GameObject.h"

GameObject::GameObject()
{
	transform = new Transform();
	meshRenderer = new MeshRenderer();
}

glm::vec3 GameObject::GetForward() const
{
    glm::vec3 forward;
    forward.x = cos(glm::radians(transform->rotation.x)) * cos(glm::radians(transform->rotation.y));
    forward.y = sin(glm::radians(transform->rotation.y));
    forward.z = sin(glm::radians(transform->rotation.x)) * cos(glm::radians(transform->rotation.y));
    return glm::normalize(forward);
}

void GameObject::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {}

GameObject::~GameObject()
{
	delete transform;
	delete meshRenderer;
}

void GameObject::SetTag(std::string newTag) { tag = newTag; }
