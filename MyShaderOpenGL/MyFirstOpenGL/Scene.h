#pragma once
#include <vector>
#include <string>
#include <glm.hpp>
#include "GameObject.h"
#include "Camera.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "LightData.h"
#include "DirectionalLight.h"

class Scene {
protected:

	Camera* camera = nullptr;

	// Luz ambiente
	glm::vec3 ambientColor = glm::vec3(0.9f, 0.85f, 0.6f);
	float ambientIntensity = 0.35f;

	std::vector<GameObject*> objects;

public:
	Scene() = default;
	virtual ~Scene();

	virtual void OnEnter() = 0;
	
	virtual void OnExit();

	virtual void Update(float dt);

	virtual void Render();

	GameObject* FindByTag(const std::string& tag);

	void AddGameObject(GameObject* obj);

	std::vector<GameObject*>& GetObjects() { return objects; }

	// solo luces
	std::vector<Light*> GetLights();
};
