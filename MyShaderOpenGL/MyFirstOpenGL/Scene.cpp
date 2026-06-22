#include "Scene.h"

Scene::~Scene()
{
	OnExit();
}

void Scene::OnExit()
{
	delete camera;
	camera = nullptr;

	for (GameObject* o : objects) {
		delete o;
	}
	objects.clear();
}

void Scene::Update(float dt)
{
	for (short i = objects.size() - 1; i >= 0; i--) {
		if (objects[i]->isPendingDestroy) {
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
	}

	camera->Update(dt);

	for (GameObject* o : objects) {
		if (o != nullptr && o->isVisible) {
			o->Update(dt);
		}
	}
}

void Scene::Render()
{
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glm::mat4 projectionMatrix = camera->GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);


	for (GameObject* o : objects) {
		if (o != nullptr && o->isVisible) {
			o->Render(viewMatrix, projectionMatrix);
		}
	}
}

void Scene::AddGameObject(GameObject* obj) { if (obj != nullptr) objects.push_back(obj); }

std::vector<Light*> Scene::GetLights()
{
	std::vector<Light*> lights;
	for (GameObject* o : objects)
	{
		Light* l = dynamic_cast<Light*>(o);
		if (l) lights.push_back(l);
	}
	return lights;
}

GameObject* Scene::FindByTag(const std::string& tag)
{
	for (GameObject* o : objects)
	{
		if (o->tag == tag)
			return o;
	}
	return nullptr;
}