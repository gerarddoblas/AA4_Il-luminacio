#pragma once
#include <glm.hpp>
#include "Transform.h"
#include <string>
#include "MeshRenderer.h"

class GameObject
{
protected:
	Transform* transform = nullptr;
	MeshRenderer* meshRenderer = nullptr;

public:
	bool isVisible = true;
	float speed = 1.0f;
	bool isPendingDestroy = false;
	std::string tag = "";

	GameObject();
	virtual ~GameObject();
	void SetTag(std::string newTag);
	virtual void Update(float dt) = 0;

	virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

	Transform* GetTransform() const { return transform; }
	MeshRenderer* GetMeshRenderer() const { return meshRenderer; }
};
