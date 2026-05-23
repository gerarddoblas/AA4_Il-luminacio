#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Cube.h"
#include "ModelObject.h"

class MainScene : public Scene {
public:
    void OnEnter() override;

    void Update(float dt) override;
};
