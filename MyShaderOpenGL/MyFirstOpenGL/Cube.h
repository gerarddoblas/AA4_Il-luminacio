#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
public:
public:
    Cube(glm::vec3 position, glm::vec3 scale);

    void Update(float dt) override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
    GLuint shaderProgram = 0;
    const int vertexCount = 36;
};