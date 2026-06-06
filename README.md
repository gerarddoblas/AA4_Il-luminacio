# AA4_Il-luminacio

Uso de la IA:

A sido utilizada para ayudar a solventar errores de codigo relacionados con el movimiento de la camara.
Se a utilizado para revisar y mejorar codigo relasionado con el movimiento de la camara.
A ayudado con la rotacion y movimiento de la camara (principalmente aportando las formulas).
A propuesto utilizar la variable "bool firstMouseRead" para evitar posibles problemas (y se ha decidido utilizarlo).

Codigo de la IA:
bool firstMouseRead = true;
if(firstMouseRead)
{
    prevMouseX = mouseX;
    prevMouseY = mouseY;
    firstMouseRead = false;
}

 if (IM->GetKey(GLFW_KEY_W, HOLD) || IM->GetKey(GLFW_KEY_W, DOWN))
     transform->position += forward * moveSpeed * dt;
...

glm::vec3 Camera::GetForward() const
{
    glm::vec3 forward;
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(forward);
}


PREGUNTA:
Oye estoy haciendo una guarrada haciendo que dayNightCycle sepa sobre la escena puedes ayudarme a arreglarlo

RESPUESTA: 
Se usa esto (una función Lambda o Callback) por una regla de oro en programación de motores de videojuegos: la independencia (desacoplamiento).

dayNightCycle->onAmbientChanged = [this](glm::vec3 color, float intensity)
    {
        ambientColor     = color;
        ambientIntensity = intensity;
    };
Lo que hacemos con ese bloque de código es darle un "teléfono" al matemático. Le decimos: "No te preocupes por quién es el jefe ni cómo funciona la escena. Tú dedícate a calcular tu color y, cuando lo tengas, simplemente grítalo por este teléfono (onAmbientChanged)."

Ese bloque que has pegado es la Escena diciendo: "Yo ([this]) me quedo al otro lado del teléfono escuchando. Cuando el ciclo de día y noche grite el nuevo color, yo me encargaré de actualizar mis propias variables internas (ambientColor = color;)."

De esta forma, ambas clases se comunican perfectamente en cada fotograma, pero sus códigos son 100% independientes y limpios.



PREGUNTA
PUEDES Ayudarme a como hacer que den la vuelta alrededor de la escena, y que haya un amanecer, medianoche y mediodía y el color dependiendo de la hora

#include "DayNightCycle.h"
#include <gtc/matrix_transform.hpp>

DayNightCycle::DayNightCycle(DirectionalLight* sun, DirectionalLight* moon)
    : sun(sun), moon(moon)
{
    delete meshRenderer;
    meshRenderer = nullptr;
}

void DayNightCycle::Update(float dt)
{
    
    float degreesPerSecond = 360.0f / cycleDuration;
    angleDeg += degreesPerSecond * dt;
    if (angleDeg >= 360.0f) angleDeg -= 360.0f;

    //180 grados entre si
    ApplyOrbitToLight(sun,  angleDeg);
    ApplyOrbitToLight(moon, angleDeg + 180.0f);

  }

void DayNightCycle::ApplyOrbitToLight(DirectionalLight* light, float deg)
{
    // Z fijo
    
    float rad = glm::radians(deg);
    glm::vec3 pos = glm::vec3(sin(rad) * orbitRadius, cos(rad) * orbitRadius, 0.0f);
    light->GetTransform()->position = pos;

    // direccion luz
    glm::vec3 dir = glm::normalize(-pos);

       // solo ilumina si Y positiva
    float sunHeight = pos.y;
    light->isVisible = (sunHeight > 0.0f);




RESPUESTA

#include "DayNightCycle.h"
#include <gtc/matrix_transform.hpp>
#include <algorithm>

DayNightCycle::DayNightCycle(DirectionalLight* sun, DirectionalLight* moon)
    : sun(sun), moon(moon)
{
    delete meshRenderer;
    meshRenderer = nullptr;
}

void DayNightCycle::Update(float dt)
{
    
    float degreesPerSecond = 360.0f / cycleDuration;
    angleDeg += degreesPerSecond * dt;
    if (angleDeg >= 360.0f) angleDeg -= 360.0f;

    //180 grados entre si
    ApplyOrbitToLight(sun,  angleDeg);
    ApplyOrbitToLight(moon, angleDeg + 180.0f);

    // angulo 90 = sol
    float t = sin(glm::radians(angleDeg));

    // Calculamos el ambient de este momento y avisamos a quien escuche
    if (onAmbientChanged)
    {
        onAmbientChanged(CalcAmbientColor(t), CalcAmbientIntensity(t));
    }
}

void DayNightCycle::ApplyOrbitToLight(DirectionalLight* light, float deg)
{
    // Z fijo
    
    float rad = glm::radians(deg);
    glm::vec3 pos = glm::vec3(sin(rad) * orbitRadius, cos(rad) * orbitRadius, 0.0f);
    light->GetTransform()->position = pos;

    // direccion luz
    glm::vec3 dir = glm::normalize(-pos);

    // Convertimos la direccion a yaw/pitch para que GetDirection() devuelva lo correcto
    // pitch = asin(dir.y),  yaw = atan2(dir.z, dir.x)
    //IA
    float pitch = glm::degrees(asin(dir.y));
    float yaw = glm::degrees(atan2(dir.z, dir.x));
    light->GetTransform()->rotation = glm::vec3(yaw, pitch, 0.0f);

    // solo ilumina si Y positiva
    float sunHeight = pos.y;
    light->isVisible = (sunHeight > 0.0f);
}

glm::vec3 DayNightCycle::CalcAmbientColor(float t) const
{
    
    // t: -1 = medianoche, 0 = amanecer/atardecer, 1 = mediodia
    glm::vec3 night = glm::vec3(0.05f, 0.05f, 0.15f);
    glm::vec3 day   = glm::vec3(0.9f,  0.85f, 0.6f);
    float factor = (t + 1.0f) * 0.5f;
    return glm::mix(night, day, factor);
}

float DayNightCycle::CalcAmbientIntensity(float t) const
{
    // De noche el ambiente es debil (0.05), de dia es visible (0.35)
    float factor = (t + 1.0f) * 0.5f;
    return glm::mix(0.05f, 0.35f, factor);
}

Pregunta
asi como has hehco el cpp puedes hacer el .h 
class DayNightCycle : public GameObject
{
public:
    float cycleDuration = 20.0f;
    float orbitRadius   = 8.0f;

    DayNightCycle(DirectionalLight* sun, DirectionalLight* moon);

    void Update(float dt) override;
    void Render(const glm::mat4& view, const glm::mat4& proj, const LightData& lights) override {}

    float GetAngleDeg() const { return angleDeg; }

private:
    DirectionalLight* sun  = nullptr;
    DirectionalLight* moon = nullptr;
    float angleDeg         = 0.0f;

    // Calcula la direccion del astro dado su angulo en la orbita
    void ApplyOrbitToLight(DirectionalLight* light, float deg);

 
};

RESPUESTA

#pragma once
#include "GameObject.h"
#include "DirectionalLight.h"
#include "LightData.h"
#include <glm.hpp>
#include <functional>

// Controla el ciclo dia/noche - orbita el sol y la luna
// y modifica el ambient que se expone a la escena mediante el callback
class DayNightCycle : public GameObject
{
public:
    float cycleDuration = 20.0f; // segundos por ciclo completo
    float orbitRadius   = 8.0f;

    // Callback que la escena puede usar para recibir el ambient calculado
    std::function<void(glm::vec3 color, float intensity)> onAmbientChanged;

    DayNightCycle(DirectionalLight* sun, DirectionalLight* moon);

    void Update(float dt) override;
    void Render(const glm::mat4& view, const glm::mat4& proj, const LightData& lights) override {}

    float GetAngleDeg() const { return angleDeg; }

private:
    DirectionalLight* sun  = nullptr;
    DirectionalLight* moon = nullptr;
    float angleDeg         = 0.0f; // angulo actual de la orbita

    // Calcula la direccion del astro dado su angulo en la orbita
    void ApplyOrbitToLight(DirectionalLight* light, float deg);

    // Interpola el color ambient entre medianoche y mediodia
    glm::vec3 CalcAmbientColor(float t) const;
    float     CalcAmbientIntensity(float t) const;
};


PREGUNTA:
Ahora mismo mando las luces por shader escrito tal cual, como harias tu que pudiera tener varias luces en tiempo real?
Habia pensado algo como unity de light

algo como 
struct LightData
{

    //directional light
    glm::vec3 sunDirection  = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 sunColor = glm::vec3(1.0f, 0.95f, 0.8f);
    
       glm::vec3 moonDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 moonColor = glm::vec3(0.4f, 0.5f, 0.8f);
  
};


RESPUESTA:
tu idea de hacer un struct LightData al estilo Unity es la solución profesional estándar (conocida en la industria como Forward Rendering) por tres grandes razones:

Orden mental y escalabilidad (Como Unity): En lugar de tener la función Render pidiendo 14 variables sueltas (float sunX, float sunY, float sunR...), empaquetas todo en una sola "caja" (tu LightData). Si mañana decides añadir fuego, farolas o linternas, solo añades variables a tu struct y el resto del motor gráfico ni se entera ni se rompe.
CPU vs GPU: Te habría dicho que la tarjeta gráfica (GPU) es muy rápida pintando, pero muy tonta pensando. Tu idea de tener el LightData en C++ permite que el procesador de tu ordenador (CPU) haga los cálculos difíciles (trigonometría, rotaciones del sol) y una vez que tiene el resultado, mete los números finales en el LightData y se lo manda a la GPU machacadito y listo para pintar.
Reutilización: Al tener ese struct, puedes tener 500 modelos en pantalla (trolls, rocas, nubes) y a los 500 les pasas exactamente la misma copia de tu LightData.Pero recomiendo los cambios siguientes para estar en linea  con la practica que me pasaste.

struct LightData
{
    // Luz ambiente 
    glm::vec3 ambientColor = glm::vec3(1.0f);
    float ambientIntensity = 0.1f;

    //directional light
    glm::vec3 sunDirection  = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 sunColor = glm::vec3(1.0f, 0.95f, 0.8f);
    float sunIntensity  = 1.0f;
    float sunActive = 1.0f; // 1 si el sol esta por encima del horizonte, 0 si no

    // directional light a 180 grados
    glm::vec3 moonDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 moonColor = glm::vec3(0.4f, 0.5f, 0.8f);
    float moonIntensity  = 0.4f;
    float moonActive   = 0.0f;
};


PREGUNTA:
Como calculo el forward de la directional light? tengo esta función y he intentado sacar la Z pero no lo hace, haz solo el codigo
glm::vec3 DirectionalLight::GetDirection()
{

    return transform->rotation.z;
}

Respuesta
glm::vec3 DirectionalLight::GetDirection() const
{
    // forward
    float yaw   = transform->rotation.x;
    float pitch = transform->rotation.y;

    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(dir);
}

Pregunta: Me puedes ayudar a hacer los shaders que te pase? voy muy perdido hazlos según la ficha que te pase y lo que sabes del proyecto. y de paso haz los Uniforms a pasar

#version 440 core

in vec3 FragNormal;
in vec3 FragPos;

// Color base del cubo
uniform vec3 baseColor;

// Luz ambiente
uniform vec3  ambientColor;
uniform float ambientIntensity;

// Sol
uniform vec3  sunDirection;
uniform vec3  sunColor;
uniform float sunIntensity;
uniform float sunActive;

// Luna
uniform vec3  moonDirection;
uniform vec3  moonColor;
uniform float moonIntensity;
uniform float moonActive;

// Linterna
uniform vec3  spotPosition;
uniform vec3  spotDirection;
uniform vec3  spotColor;
uniform float spotIntensity;
uniform float spotInnerCos;
uniform float spotOuterCos;
uniform float spotRange;
uniform int   spotEnabled;

out vec4 fragColor;

vec3 CalcDirectional(vec3 dir, vec3 lightColor, float intensity, float isActive)
{
    float diff = max(dot(FragNormal, -normalize(dir)), 0.15);
    return lightColor * intensity * diff * isActive;
}

vec3 CalcSpot()
{
    if (spotEnabled == 0) return vec3(0.0);

    vec3  toFrag = FragPos - spotPosition;
    float dist   = length(toFrag);
    if (dist > spotRange) return vec3(0.0);

    vec3  fragDir = normalize(toFrag);
    float cosA    = dot(fragDir, normalize(spotDirection));

    if (cosA < spotOuterCos) return vec3(0.0);

    float epsilon = spotInnerCos - spotOuterCos;
    float cone    = clamp((cosA - spotOuterCos) / epsilon, 0.0, 1.0);
    float atten   = 1.0 - clamp(dist / spotRange, 0.0, 1.0);
    atten         = atten * atten;

    float diff    = max(dot(FragNormal, -fragDir), 0.0);
    return spotColor * spotIntensity * diff * cone * atten;
}

void main()
{
    vec3 ambient  = ambientColor * ambientIntensity;
    vec3 sun      = CalcDirectional(sunDirection,  sunColor,  sunIntensity,  sunActive);
    vec3 moon     = CalcDirectional(moonDirection, moonColor, moonIntensity, moonActive);
    vec3 spot     = CalcSpot();

    vec3 lighting = ambient + sun + moon;
    fragColor     = vec4(baseColor * lighting, 1.0);
}


#version 440 core

layout(location = 0) in vec3 posicion;
layout(location = 1) in vec3 inNormal;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 scaleMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 FragNormal;
out vec3 FragPos;

void main()
{
    mat4 model   = translationMatrix * rotationMatrix * scaleMatrix;
    vec4 worldPos = model * vec4(posicion, 1.0);

    FragPos = worldPos.xyz;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    FragNormal = normalize(normalMatrix * inNormal);

    gl_Position = projectionMatrix * viewMatrix * worldPos;
}

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

void ModelObject::Update(float dt) {}

void ModelObject::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const LightData& lights)
{
	if (!isVisible) return;

	glUseProgram(shaderProgram);

	// Transform
	glm::mat4 modelMat = transform->GetModelMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelMatrix"),1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Tint del Color
	glUniform4fv(glGetUniformLocation(shaderProgram, "tintColor"), 1, glm::value_ptr(tintColor));

	// Unlit flag
	glUniform1i(glGetUniformLocation(shaderProgram, "isUnlit"), isUnlit ? 1 : 0);

	// Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shaderProgram, "textureSampler"), 0);

	// Ambiente
	glUniform3fv(glGetUniformLocation(shaderProgram, "ambientColor"), 1, glm::value_ptr(lights.ambientColor));
	glUniform1f (glGetUniformLocation(shaderProgram, "ambientIntensity"), lights.ambientIntensity);

	// Sol
	glUniform3fv(glGetUniformLocation(shaderProgram, "sunDirection"), 1, glm::value_ptr(lights.sunDirection));
	glUniform3fv(glGetUniformLocation(shaderProgram, "sunColor"),  1, glm::value_ptr(lights.sunColor));
	glUniform1f (glGetUniformLocation(shaderProgram, "sunIntensity"), lights.sunIntensity);
	glUniform1f (glGetUniformLocation(shaderProgram, "sunActive"), lights.sunActive);

	// Luna
	glUniform3fv(glGetUniformLocation(shaderProgram, "moonDirection"),1, glm::value_ptr(lights.moonDirection));
	glUniform3fv(glGetUniformLocation(shaderProgram, "moonColor"), 1, glm::value_ptr(lights.moonColor));
	glUniform1f (glGetUniformLocation(shaderProgram, "moonIntensity"),lights.moonIntensity);
	glUniform1f (glGetUniformLocation(shaderProgram, "moonActive"), lights.moonActive);
// Renderizo modelo
	model->Render();

	glUseProgram(0);
}

Pregunta
Como paso las lights por la escena para que se pinten en realTime

RESPUESTA

void Scene::Render()
{
    // Obtenemos la posición y perspectiva de la cámara
    glm::mat4 viewMatrix       = camera->GetViewMatrix();
    glm::mat4 projectionMatrix = camera->GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);
    // PASO 1: Preparamos el "maletín" vacío (LightData) y le metemos el color ambiente
    LightData lights;
    lights.ambientColor     = ambientColor;
    lights.ambientIntensity = ambientIntensity;
    // PASO 2: Hacemos un barrido para buscar al Sol y a la Luna y robarles sus datos
    for (GameObject* o : objects)
    {
        DirectionalLight* dl = dynamic_cast<DirectionalLight*>(o);
        if (dl)
        {
            if (dl->tag == "sun")
            {
                lights.sunDirection = dl->GetDirection();
                lights.sunColor     = dl->color;
                lights.sunIntensity = dl->intensity;
                lights.sunActive    = dl->isVisible ? 1.0f : 0.0f; // 0.0f si bajó del suelo
            }
            else if (dl->tag == "moon")
            {
                lights.moonDirection = dl->GetDirection();
                lights.moonColor     = dl->color;
                lights.moonIntensity = dl->intensity;
                lights.moonActive    = dl->isVisible ? 1.0f : 0.0f;
            }
        }
    }
    // PASO 3: Hacemos un último barrido enviando el "maletín" lleno (lights) a todo el mundo
    for (GameObject* o : objects) {
        if (o != nullptr && o->isVisible) {
            
            // Aquí es donde se lo enchufamos a los Trolls, Rocas y el Suelo
            o->Render(viewMatrix, projectionMatrix, lights);
            
        }
    }
}

Pregunta: Lo mismo de las luces lo puedes hacer para el daynight cycle que te acabo de pasar 

Respuesta:
void DayNightCycle::Update(float dt)
{
    
    float degreesPerSecond = 360.0f / cycleDuration;
    angleDeg += degreesPerSecond * dt;
    if (angleDeg >= 360.0f) angleDeg -= 360.0f;

    //180 grados entre si
    ApplyOrbitToLight(sun,  angleDeg);
    ApplyOrbitToLight(moon, angleDeg + 180.0f);

    // angulo 90 = sol
    float t = sin(glm::radians(angleDeg));

    // Calculamos el ambient de este momento y avisamos a quien escuche
    if (onAmbientChanged)
    {
        onAmbientChanged(CalcAmbientColor(t), CalcAmbientIntensity(t));
    }
}

void DayNightCycle::ApplyOrbitToLight(DirectionalLight* light, float deg)
{
    // Z fijo
    
    float rad = glm::radians(deg);
    glm::vec3 pos = glm::vec3(sin(rad) * orbitRadius, cos(rad) * orbitRadius, 0.0f);
    light->GetTransform()->position = pos;

    // direccion luz
    glm::vec3 dir = glm::normalize(-pos);

    // Convertimos la direccion a yaw/pitch para que GetDirection() devuelva lo correcto
    // pitch = asin(dir.y),  yaw = atan2(dir.z, dir.x)
    //IA
    float pitch = glm::degrees(asin(dir.y));
    float yaw = glm::degrees(atan2(dir.z, dir.x));
    light->GetTransform()->rotation = glm::vec3(yaw, pitch, 0.0f);

    // solo ilumina si Y positiva
    float sunHeight = pos.y;
    light->isVisible = (sunHeight > 0.0f);
}

glm::vec3 DayNightCycle::CalcAmbientColor(float t) const
{
    
    // t: -1 = medianoche, 0 = amanecer/atardecer, 1 = mediodia
    glm::vec3 night = glm::vec3(0.05f, 0.05f, 0.15f);
    glm::vec3 day   = glm::vec3(0.9f,  0.85f, 0.6f);
    float factor = (t + 1.0f) * 0.5f;
    return glm::mix(night, day, factor);
}

float DayNightCycle::CalcAmbientIntensity(float t) const
{
    // De noche el ambiente es debil (0.05), de dia es visible (0.35)
    float factor = (t + 1.0f) * 0.5f;
    return glm::mix(0.05f, 0.35f, factor);

}

PREGUNTA: EL cube que te he pasado le faltan los nuevos VBO y los vao ponlos

RESPUESTA: #include "Cube.h"
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


Tambien se ha utilizado los LLM para la siguiente tool


Prompt:

Estoy reutilizando el código para hacer que la escala y la rotación sea aleatoria, puedes ayudarme a optimizar esto en mi clase Utils.h y .cpp sin que tenga que hacer copycat?

Respuesta:
float RandomRange(float min, float max) { return min + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (max - min); }


Prompot 2nd:

Puedes ajustar la posición de los GameObjects al tamaño del Ground?

Respuesta:

const glm::vec3 SPAWN_POINTS[] =
{
    // Fila cercana  (Z: -4 a -6)
    glm::vec3(-7.0f, -0.8f,  -4.0f),
    glm::vec3( 0.0f, -0.8f,  -4.0f),
    glm::vec3( 7.0f, -0.8f,  -4.0f),
    glm::vec3(-4.0f, -0.8f,  -6.0f),
    glm::vec3( 4.0f, -0.8f,  -6.0f),
    // Fila media  (Z: -7 a -9)
    glm::vec3(-8.0f, -0.8f,  -7.0f),
    glm::vec3(-3.0f, -0.8f,  -8.0f),
    glm::vec3( 0.0f, -0.8f,  -9.0f),
    glm::vec3( 3.0f, -0.8f,  -8.0f),
    glm::vec3( 8.0f, -0.8f,  -7.0f),
    // Fila lejana  (Z: -10 a -12)
    glm::vec3(-8.0f, -0.8f, -10.0f),
    glm::vec3(-5.0f, -0.8f, -11.0f),
    glm::vec3( 0.0f, -0.8f, -12.0f),
    glm::vec3( 5.0f, -0.8f, -11.0f),
    glm::vec3( 8.0f, -0.8f, -10.0f),
    // Extremos del suelo  (Z: -12)
    glm::vec3(-8.0f, -0.8f, -12.0f),
    glm::vec3(-4.0f, -0.8f, -12.0f),
    glm::vec3( 0.0f, -0.8f, -12.0f),
    glm::vec3( 4.0f, -0.8f, -12.0f),
    glm::vec3( 8.0f, -0.8f, -12.0f),
    glm::vec3( 0.0f, -0.8f,  6.0f), // Punto delante de la camara
};
constexpr short NUM_SPAWN_POINTS = 21;