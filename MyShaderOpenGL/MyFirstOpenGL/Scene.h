#pragma once
#include <vector>
#include <string>
#include <glm.hpp>
#include "GameObject.h"
#include "Camera.h"
#include "RenderManager.h"
#include "InputManager.h"

class Scene {
protected:

	Camera* camera = nullptr;

	std::vector<GameObject*> objects;

public:
	Scene() = default;
	virtual ~Scene();

	virtual void OnEnter() = 0;
	
	virtual void OnExit();

	virtual void Update(float dt);

	virtual void Render();

	GameObject* FindByTag(const std::string& tag);

	// Metodo para añadir objetos a la escena
	void AddGameObject(GameObject* obj);

	std::vector<GameObject*>& GetObjects() { return objects; }
};
