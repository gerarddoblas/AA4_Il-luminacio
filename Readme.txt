# AA3_3DModels-Camera

Edgar Novas, Gerard Doblas, Nil Barrero

Uso de la IA para:

Revisión de magic numbers y optimización de código.

Posiciones de los distintos elementos en el mapa y revisar código.

Codigo hecho con IA:

El código no es lo que esta hecho con la IA, simplemente se le ha pedido las posiciones, rotaciones, colores, etc.

 //Trolls
 ModelObject* troll1 = new ModelObject("../Assets/Modelos/troll.obj", "../Assets/Texturas/troll.png");
 troll1->GetTransform()->position = glm::vec3(0.0f, -0.8f, -1.0f);
 troll1->GetTransform()->scale = glm::vec3(0.3f);
 troll1->GetTransform()->rotation = glm::vec3(90.0f, 0.0f, 0.0f); 
 troll1->SetTag("troll1");
 AddGameObject(troll1);

 ModelObject* troll2 = new ModelObject("../Assets/Modelos/troll.obj", "../Assets/Texturas/troll.png");
 troll2->GetTransform()->position = glm::vec3(-1.0f, -0.8f, -0.5f);
 troll2->GetTransform()->scale = glm::vec3(0.3f);
 troll2->GetTransform()->rotation = glm::vec3(0.0f, 90.0f, 0.0f); 
 troll2->SetTintColor(glm::vec4(3.0f, 0.0f, 0.0f, 1.0f)); // Rojo
 troll2->SetTag("troll2");
 AddGameObject(troll2);

 ModelObject* troll3 = new ModelObject("../Assets/Modelos/troll.obj", "../Assets/Texturas/troll.png");
 troll3->GetTransform()->position = glm::vec3(1.0f, -0.8f, -2.0f);
 troll3->GetTransform()->scale = glm::vec3(0.3f);;
 troll3->SetTintColor(glm::vec4(3.0f, 2.5f, 0.0f, 1.0f)); // Amarillo
 troll3->SetTag("troll3");
 AddGameObject(troll3);

 ModelObject* troll4 = new ModelObject("../Assets/Modelos/troll.obj", "../Assets/Texturas/troll.png");
 troll4->GetTransform()->position = glm::vec3(-0.5f, -0.8f, -2.5f);
 troll4->GetTransform()->scale = glm::vec3(0.3f);
 troll4->GetTransform()->rotation = glm::vec3(0.0f, 180.0f, 0.0f);
 troll4->SetTintColor(glm::vec4(1.5f, 0.8f, 0.2f, 1.0f)); // Marrón
 troll4->SetTag("troll4");
 AddGameObject(troll4);

 //Rocks alrededor de los trolls
 ModelObject* rock = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock->GetTransform()->position = glm::vec3(0.5f, -0.8f, 0.5f);
 rock->GetTransform()->scale = glm::vec3(0.3f);
 rock->GetTransform()->rotation = glm::vec3(90.0f, 0.0f, 0.0f);
 AddGameObject(rock);

 ModelObject* rock2 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock2->GetTransform()->position = glm::vec3(-1.8f, -0.8f, 0.0f);
 rock2->GetTransform()->scale = glm::vec3(0.3f);
 rock2->GetTransform()->rotation = glm::vec3(90.0f, 20.0f, 0.0f);
 AddGameObject(rock2);

 ModelObject* rock3 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock3->GetTransform()->position = glm::vec3(1.8f, -0.8f, 0.0f);
 rock3->GetTransform()->scale = glm::vec3(0.3f);
 rock3->GetTransform()->rotation = glm::vec3(90.0f, 75.0f, 0.0f);
 AddGameObject(rock3);

 ModelObject* rock4 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock4->GetTransform()->position = glm::vec3(-1.8f, -0.8f, -2.0f);
 rock4->GetTransform()->scale = glm::vec3(0.3f);
 rock4->GetTransform()->rotation = glm::vec3(90.0f, 110.0f, 0.0f);
 AddGameObject(rock4);

 ModelObject* rock5 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock5->GetTransform()->position = glm::vec3(1.8f, -0.8f, -2.0f);
 rock5->GetTransform()->scale = glm::vec3(0.3f);
 rock5->GetTransform()->rotation = glm::vec3(90.0f, 160.0f, 0.0f);
 AddGameObject(rock5);

 ModelObject* rock6 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock6->GetTransform()->position = glm::vec3(-1.8f, -0.8f, -4.0f);
 rock6->GetTransform()->scale = glm::vec3(0.3f);
 rock6->GetTransform()->rotation = glm::vec3(90.0f, 200.0f, 0.0f);
 AddGameObject(rock6);

 ModelObject* rock7 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock7->GetTransform()->position = glm::vec3(1.8f, -0.8f, -4.0f);
 rock7->GetTransform()->scale = glm::vec3(0.3f);
 rock7->GetTransform()->rotation = glm::vec3(90.0f, 240.0f, 0.0f);
 AddGameObject(rock7);

 ModelObject* rock8 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock8->GetTransform()->position = glm::vec3(0.0f, -0.8f, -5.0f);
 rock8->GetTransform()->scale = glm::vec3(0.3f);
 rock8->GetTransform()->rotation = glm::vec3(90.0f, 300.0f, 0.0f);
 AddGameObject(rock8);

 // Rocas entre los trolls
 ModelObject* rock9 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock9->GetTransform()->position = glm::vec3(-0.5f, -0.8f, -1.5f);
 rock9->GetTransform()->scale = glm::vec3(0.2f);
 rock9->GetTransform()->rotation = glm::vec3(90.0f, 45.0f, 0.0f);
 AddGameObject(rock9);

 ModelObject* rock10 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock10->GetTransform()->position = glm::vec3(0.5f, -0.8f, -3.0f);
 rock10->GetTransform()->scale = glm::vec3(0.2f);
 rock10->GetTransform()->rotation = glm::vec3(90.0f, 130.0f, 0.0f);
 AddGameObject(rock10);

 ModelObject* rock11 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 rock11->GetTransform()->position = glm::vec3(-0.3f, -0.8f, -3.5f);
 rock11->GetTransform()->scale = glm::vec3(0.15f);
 rock11->GetTransform()->rotation = glm::vec3(90.0f, 80.0f, 0.0f);
 AddGameObject(rock11);


 //Nubes
 ModelObject* nube = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 nube->GetTransform()->position = glm::vec3(-3.0f, 1.5f, -2.0f);
 nube->GetTransform()->scale = glm::vec3(0.3f);
 nube->GetTransform()->rotation = glm::vec3(90.0f, 0.0f, 0.0f);
 nube->SetTintColor(glm::vec4(3.0f, 3.0f, 3.0f, 1.0f));
 AddGameObject(nube);

 ModelObject* nube2 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 nube2->GetTransform()->position = glm::vec3(3.5f, 1.5f, -3.0f);
 nube2->GetTransform()->scale = glm::vec3(0.2f);
 nube2->GetTransform()->rotation = glm::vec3(90.0f, 45.0f, 0.0f);
 nube2->SetTintColor(glm::vec4(3.0f, 3.0f, 3.0f, 1.0f));
 AddGameObject(nube2);
 
 ModelObject* nube3 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 nube3->GetTransform()->position = glm::vec3(4.0f, 1.3f, -1.5f);
 nube3->GetTransform()->scale = glm::vec3(0.28f);
 nube3->GetTransform()->rotation = glm::vec3(90.0f, 30.0f, 15.0f);
 nube3->SetTintColor(glm::vec4(3.0f, 3.0f, 3.0f, 1.0f));
 AddGameObject(nube3);
 
 ModelObject* nube4 = new ModelObject("../Assets/Modelos/rock.obj", "../Assets/Texturas/rock.png");
 nube4->GetTransform()->position = glm::vec3(-3.5f, 1.4f, -1.0f);
 nube4->GetTransform()->scale = glm::vec3(0.20f);
 nube4->GetTransform()->rotation = glm::vec3(90.0f, 55.0f, 30.0f);
 nube4->SetTintColor(glm::vec4(3.0f, 3.0f, 3.0f, 1.0f));
 AddGameObject(nube4);
 
 1R PROMPT

Con lo que sabes del proyecto puedes crearme los shaders y el tint, deja mis comentarios como estan(ya he pasado antes el cpp)

class ModelObject : public GameObject
{
public:
    ModelObject(const std::string& modelPath, const std::string& texturePath);
    ~ModelObject() override;


    void Update(float dt) override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;


private:
    Model* model = nullptr;
};

Respuesta dada

He añadido los shaders de textura (TextureVertexShader.glsl y TextureFragmentShader.glsl) y el código que los enlaza dentro de ModelObject.cpp 
¿Hay alguna cosita del código que quieras repasar o alguna otra cosa en la que pueda echarte una mano? 

#pragma once
#include "GameObject.h"
#include "Model.h"
#include "RenderManager.h"
#include <stb_image.h>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <string>


class ModelObject : public GameObject
{
public:
    ModelObject(const std::string& modelPath, const std::string& texturePath);
    ~ModelObject() override;


    void Update(float dt) override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;


    void SetTintColor(const glm::vec4& color) { tintColor = color; }


private:
    Model* model = nullptr;
    GLuint textureID = 0;
    glm::vec4 tintColor = glm::vec4(1.0f); //Blanco by default
    GLuint shaderProgram = 0;
};








Este es el cpp que habia pasado antes ya editado
#include "ModelObject.h"




ModelObject::ModelObject(const std::string& modelPath, const std::string& texturePath)
{
    // Cargamos modelo
    Model modelParaCargarOBJ = LoadOBJModel(modelPath);
    //Lo pongo asi porque es un puntero model
    model = new Model(modelParaCargarOBJ);


    // Cargamos la textura con stb image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
       
       
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       
       
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        GLenum format = GL_RGB;
        if (nrChannels == 4) format = GL_RGBA;


        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);


        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }


    //Shaders para texturas
    RenderManager::ShaderProgram shaderStruct;
    shaderStruct.vertexShader = RM->LoadVertexShader("TextureVertexShader.glsl");
    shaderStruct.fragmentShader = RM->LoadFragmentShader("TextureFragmentShader.glsl");
    shaderProgram = RM->CreateProgram(shaderStruct);
}


ModelObject::~ModelObject()
{
    glDeleteTextures(1, &textureID);
    delete model;
}


void ModelObject::Update(float dt){}


void ModelObject::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    if (!_isVisible) return;


    glUseProgram(shaderProgram);


    // Transform
    glm::mat4 modelMat = _transform->GetModelMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));


    // Tint del Color
    glUniform4fv(glGetUniformLocation(shaderProgram, "tintColor"), 1, glm::value_ptr(tintColor));


    // Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(shaderProgram, "textureSampler"), 0);


    // Renderizo modelo
    model->Render();


    glUseProgram(0);
}



//TextureFragment

#version 440 core

in vec2 TexCoord;

uniform sampler2D textureSampler;
uniform vec4 tintColor;

out vec4 fragColor;

void main()
{
	vec4 texColor = texture(textureSampler, TexCoord);
	fragColor = texColor * tintColor;
}


//Texture VertexShader

#version 440 core

layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 TexCoord;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition, 1.0);
	TexCoord =  vec2(inTexCoord.x,1.0 - inTexCoord.y);
}



2ndo Prompt
No funciona el transform que me falta?
#include "Transform.h"
#include <gtc/matrix_transform.hpp>


glm::mat4 Transform::GenerateScaleMatrix(glm::vec3 scaleAxis) const {
    return glm::scale(glm::mat4(1.0f), scaleAxis);
}


glm::mat4 Transform::GenerateRotationMatrix(glm::vec3 axis, float degrees) const {
    return glm::rotate(glm::mat4(1.0f);
}


glm::mat4 Transform::GenerateTranslationMatrix(glm::vec3 translation) const {
    return glm::translate(glm::mat4(1.0f), translation);
}






RESPUESTA 2DO:
Tienes el glm::rotate incompleto, le faltan los parámetros:
cppglm::mat4 Transform::GenerateRotationMatrix(glm::vec3 axis, float degrees) const {
   return glm::rotate(glm::mat4(1.0f), glm::radians(degrees), axis);
}
glm::rotate pide tres cosas: la matriz base, el ángulo en radianes, y el eje. También te falta implementar GetTranslationMatrix, GetRotationMatrix, GetScaleMatrix y GetModelMatrix que declaras en el .h. Algo así:
cppglm::mat4 Transform::GetTranslationMatrix() const {
   return GenerateTranslationMatrix(position);
}
glm::mat4 Transform::GetRotationMatrix() const {
   glm::mat4 rx = GenerateRotationMatrix(glm::vec3(1,0,0), rotation.x);
   glm::mat4 ry = GenerateRotationMatrix(glm::vec3(0,1,0), rotation.y);
   glm::mat4 rz = GenerateRotationMatrix(glm::vec3(0,0,1), rotation.z);
   return rz * ry * rx;
}
glm::mat4 Transform::GetScaleMatrix() const {
   return GenerateScaleMatrix(scale);
}
glm::mat4 Transform::GetModelMatrix() const {
   return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
}
Y en el vertex shader tienes que usarla. Si tienes modelMatrix como uniform separado:
glslgl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition, 1.0);



3r PROMPT
#include "MeshRenderer.h"
#include <gtc/type_ptr.hpp>

void MeshRenderer::Init(float* vertices, int byteSize)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, byteSize, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void MeshRenderer::Draw(GLuint shaderProgram, const glm::mat4& translation, const glm::mat4& rotation, const glm::mat4& scale, const glm::mat4& view, const glm::mat4& projection, int vertexCount)
{
    glUseProgram(shaderProgram);

    // Enviamos las matrices como uniforms
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translation));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotation));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scale));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
Me falla la camara falta algo en el draw?


RESPUESTA


Sí, faltan viewMatrix y projectionMatrix en el Draw. Los estás enviando a la GPU pero sin mandarlos como uniforms:
Read current MeshRenderer
Read current MeshRenderer
El problema es exactamente ese. Tu Draw nuevo recibe view y projection como parámetros pero no los manda a la GPU con glUniformMatrix4fv. La cámara existe en CPU pero el vertex shader nunca la recibe, así que tus objetos se renderizan sin transformación de cámara (world space directamente a clip space).
El fix:
cpp
void MeshRenderer::Draw(GLuint shaderProgram,
                        const glm::mat4& translation,
                        const glm::mat4& rotation,
                        const glm::mat4& scale,
                        const glm::mat4& view,        // ← llega pero...
                        const glm::mat4& projection,  // ← llega pero...
                        int vertexCount)
{
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translation));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"),    1, GL_FALSE, glm::value_ptr(rotation));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"),       1, GL_FALSE, glm::value_ptr(scale));

    // ← FALTABAN ESTAS DOS
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"),        1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"),  1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
Y actualiza el .h para que la firma coincida:
cpp
void Draw(GLuint shaderProgram,
          const glm::mat4& translation,
          const glm::mat4& rotation,
          const glm::mat4& scale,
          const glm::mat4& view,
          const glm::mat4& projection,
          int vertexCount);
Después en cada GameObject::Render ya puedes simplificar — en lugar de hacer todos los glUniform a mano, solo llamas:
cpp
void Cube::Render(const glm::mat4& view, const glm::mat4& projection)
{
    meshRenderer->Draw(
        shaderProgram,
        transform->GenerateTranslationMatrix(transform->position),
        transform->GenerateRotationMatrix(glm::vec3(0,1,0), transform->rotation.y),
        transform->GenerateScaleMatrix(transform->scale),
        view,
        projection,
        vertexCount
    );
}
Mucho más limpio que repetir los 5 glUniform en cada objeto.


