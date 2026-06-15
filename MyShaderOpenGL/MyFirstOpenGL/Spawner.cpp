#include "Spawner.h"

void Spawner::SpawnObject(GameObject* obj)
{
	assert(obj != nullptr && "SpawnObject: obj no puede ser nullptr");
	pendingSpawn.push(obj);
}

GameObject* Spawner::PopObject()
{
	if (pendingSpawn.empty())
		return nullptr;

	GameObject* obj = pendingSpawn.front();
	pendingSpawn.pop();
	return obj;
}

void Spawner::AddRandomObject(GameObject* obj)
{
	assert(obj != nullptr && "AddRandomObject: obj no puede ser nullptr");
	randomPool.push_back(obj);
}

void Spawner::SpawnRandomObject()
{
	assert(!randomPool.empty() && "SpawnRandomObject: el pool de candidatos esta vacio");
	short index = rand() % static_cast<int>(randomPool.size());
	SpawnObject(randomPool[index]);
}

void Spawner::ClearRandomPool()
{
	randomPool.clear();
}

void Spawner::DiscardPending()
{
	while (!pendingSpawn.empty())
	{
		delete pendingSpawn.front();
		pendingSpawn.pop();
	}
}
