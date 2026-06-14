#pragma once
#include "GameObject.h"
#include "LightData.h"

class Cube : public GameObject
{
public:
    Cube(glm::vec3 position, glm::vec3 scale);

    void Update(float dt) override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const LightData& lights) override;

    glm::vec3 baseColor = glm::vec3(0.35f, 0.6f, 0.25f);//Verde

private:
    GLuint shaderProgram = 0;
    GLuint vao = 0;
    GLuint vbo = 0;
    const int vertexCount = 36;
};