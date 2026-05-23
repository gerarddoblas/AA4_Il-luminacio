#include "GameObject.h"

GameObject::GameObject()
{
	transform = new Transform();
	meshRenderer = new MeshRenderer();
}

void GameObject::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {}

GameObject::~GameObject()
{
	delete transform;
	delete meshRenderer;
}

void GameObject::SetTag(std::string newTag) { tag = newTag; }
