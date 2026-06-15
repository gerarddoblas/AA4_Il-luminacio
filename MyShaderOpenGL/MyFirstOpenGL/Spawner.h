#pragma once
#pragma once
#include <queue>
#include <vector>
#include <cassert>
#include "GameObject.h"

// Macro de acceso rapido al singleton
#define SPAWNER Spawner::Instance()

class Spawner
{
public:

    static Spawner& Instance()
    {
        static Spawner spawner;
        return spawner;
    }

    void SpawnObject(GameObject* obj);

    // Devuelve true si hay objetos esperando ser añadidos a la escena.
    bool HasPendingObjects() const { return !pendingSpawn.empty(); }

    GameObject* PopObject();

    void AddRandomObject(GameObject* obj);

    void SpawnRandomObject();

    void ClearRandomPool();

    void DiscardPending();

private:
    Spawner() = default;
    Spawner(const Spawner&) = delete;
    Spawner& operator=(const Spawner&) = delete;

    std::queue<GameObject*> pendingSpawn;
    std::vector<GameObject*> randomPool;
};