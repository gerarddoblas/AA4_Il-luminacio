#include "Scene.h"

Scene::~Scene()
{
	OnExit();
}

void Scene::OnExit()
{

	delete camera;
	camera = nullptr;

	// Destruimos todos los objetos de la escena
	for (GameObject* o : objects) {
		delete o;
	}
	objects.clear();
}

void Scene::Update(float dt)
{
	// Control de destruccion de objetos
	for (short i = objects.size() - 1; i >= 0; i--) {
		if (objects[i]->isPendingDestroy) {
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
	}

	//Actualizar la camara
	camera->Update(dt);

	// Actualizamos todos los objetos
	for (GameObject* o : objects) {
		if (o != nullptr && o->isVisible) {
			o->Update(dt);
		}
	}
}

void Scene::Render()
{

	// Generamos matrices de cámara
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glm::mat4 projectionMatrix = camera->GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

	// El render de la escena simplemente le pide a cada objeto que se dibuje
	for (GameObject* o : objects) {
		if (o != nullptr && o->isVisible) {
			o->Render(viewMatrix, projectionMatrix);
		}
	}
}

void Scene::AddGameObject(GameObject* obj) { if (obj != nullptr) objects.push_back(obj); }

GameObject* Scene::FindByTag(const std::string& tag)
{
	for (GameObject* o : objects)
	{
		if (o->tag == tag)
			return o;
	}
	return nullptr;
}