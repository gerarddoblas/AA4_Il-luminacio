#include "Cube.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "RenderManager.h"

Cube::Cube(glm::vec3 position, glm::vec3 scale)
{
    RenderManager::ShaderProgram shaders;
    shaders.vertexShader   = RM->LoadVertexShader("PrimitiveVertexShader.glsl");
    shaders.fragmentShader = RM->LoadFragmentShader("PrimitiveFragmentShader.glsl");
    shaderProgram = RM->CreateProgram(shaders);

    // Posicion (x,y,z) y normal (nx,ny,nz) por vertice - stride 6 floats
    float vertices[] = {
        // Cara trasera  (normal 0,0,-1)
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        // Cara frontal  (normal 0,0,1)
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        // Cara izquierda (normal -1,0,0)
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        // Cara derecha  (normal 1,0,0)
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        // Cara inferior (normal 0,-1,0)
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        // Cara superior (normal 0,1,0)
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    };

    // VAO propio con stride 6 (pos + normal intercalados)
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // location 0 - posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // location 1 - normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    transform->position = position;
    transform->rotation = glm::vec3(0.0f);
    transform->scale    = scale;
}

void Cube::Update(float dt) {}

void Cube::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const LightData& lights)
{
    glUseProgram(shaderProgram);

    glm::mat4 T = transform->GetTranslationMatrix();
    glm::mat4 R = transform->GetRotationMatrix();
    glm::mat4 S = transform->GetScaleMatrix();

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(T));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"),    1, GL_FALSE, glm::value_ptr(R));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"),       1, GL_FALSE, glm::value_ptr(S));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"),        1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"),  1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glUniform3fv(glGetUniformLocation(shaderProgram, "baseColor"), 1, glm::value_ptr(baseColor));

    // Ambiente
    glUniform3fv(glGetUniformLocation(shaderProgram, "ambientColor"),     1, glm::value_ptr(lights.ambientColor));
    glUniform1f (glGetUniformLocation(shaderProgram, "ambientIntensity"),    lights.ambientIntensity);
    // Sol
    glUniform3fv(glGetUniformLocation(shaderProgram, "sunDirection"),  1, glm::value_ptr(lights.sunDirection));
    glUniform3fv(glGetUniformLocation(shaderProgram, "sunColor"),      1, glm::value_ptr(lights.sunColor));
    glUniform1f (glGetUniformLocation(shaderProgram, "sunIntensity"),     lights.sunIntensity);
    glUniform1f (glGetUniformLocation(shaderProgram, "sunActive"),        lights.sunActive);
    // Luna
    glUniform3fv(glGetUniformLocation(shaderProgram, "moonDirection"), 1, glm::value_ptr(lights.moonDirection));
    glUniform3fv(glGetUniformLocation(shaderProgram, "moonColor"),     1, glm::value_ptr(lights.moonColor));
    glUniform1f (glGetUniformLocation(shaderProgram, "moonIntensity"),    lights.moonIntensity);
    glUniform1f (glGetUniformLocation(shaderProgram, "moonActive"),       lights.moonActive);
glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);

    glUseProgram(0);
}