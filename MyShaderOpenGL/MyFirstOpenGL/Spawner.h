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


    void SpawnObject(GameObject* obj)
    {
        assert(obj != nullptr && "SpawnObject: obj no puede ser nullptr");
        pendingSpawn.push(obj);
    }

    // Devuelve true si hay objetos esperando ser añadidos a la escena.
    bool HasPendingObjects() const { return !pendingSpawn.empty(); }

    GameObject* PopObject()
    {
        if (pendingSpawn.empty())
            return nullptr;

        GameObject* obj = pendingSpawn.front();
        pendingSpawn.pop();
        return obj;
    }

    void AddRandomObject(GameObject* obj)
    {
        assert(obj != nullptr && "AddRandomObject: obj no puede ser nullptr");
        randomPool.push_back(obj);
    }

    void SpawnRandomObject()
    {
        assert(!randomPool.empty() && "SpawnRandomObject: el pool de candidatos esta vacio");
        int index = rand() % static_cast<int>(randomPool.size());
        SpawnObject(randomPool[index]);
    }

    void ClearRandomPool()
    {
        randomPool.clear();
    }

    void DiscardPending()
    {
        while (!pendingSpawn.empty())
        {
            delete pendingSpawn.front();
            pendingSpawn.pop();
        }
    }

private:
    Spawner() = default;
    Spawner(const Spawner&) = delete;
    Spawner& operator=(const Spawner&) = delete;

    std::queue<GameObject*>  pendingSpawn;  // Objetos listos para AddGameObject()
    std::vector<GameObject*> randomPool;    // Candidatos para spawn aleatorio
};