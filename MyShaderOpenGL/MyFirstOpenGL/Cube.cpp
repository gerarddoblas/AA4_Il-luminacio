#include "Cube.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "RenderManager.h"

Cube::Cube(glm::vec3 position, glm::vec3 scale)
{
    RenderManager::ShaderProgram shaders;
    shaders.vertexShader = RM->LoadVertexShader("PrimitiveVertexShader.glsl");
    shaders.fragmentShader = RM->LoadFragmentShader("PrimitiveFragmentShader.glsl");
    shaderProgram = RM->CreateProgram(shaders);

    float vertices[] = {
        // Cara trasera
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
         // Cara frontal
         -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
          0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,
          // Cara izquierda
          -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
          -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
          // Cara derecha
           0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
           0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
           // Cara inferior
           -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,
            // Cara superior
            -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f
    };

    meshRenderer->Init(vertices, sizeof(vertices));

    transform->position = position;
    transform->rotation = glm::vec3(0.0f);
    transform->scale = scale;
}

void Cube::Update(float dt) {}

void Cube::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    meshRenderer->Draw(shaderProgram,
        transform->GetTranslationMatrix(),
        transform->GetRotationMatrix(),
        transform->GetScaleMatrix(),
        viewMatrix, projectionMatrix, vertexCount);
}