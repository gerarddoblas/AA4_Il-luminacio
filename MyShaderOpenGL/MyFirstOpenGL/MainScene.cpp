#include "MainScene.h"
#include "Utils.h"
#include "InputManager.h"

void MainScene::OnEnter()
{
    // Camara
    camera = new Camera();

    flashlight = new SpotLight();
    flashlight->SetTag("flashlight");
    AddGameObject(flashlight);

    // Sun
    sun = new DirectionalLight();
    sun->SetTag("sun");
    sun->color = glm::vec3(1.0f, 0.95f, 0.8f);
    sun->intensity = 1.0f;
    AddGameObject(sun);

    // Visual Sun
    sunVisual = new ModelObject("../Assets/Modelos/Sun.obj", "../Assets/Texturas/Sun.png");
    sunVisual->SetUnlit(true); // Para que brille sin ser afectado por la luz
    // model del sol es enorme lo bajo la escala para poder verlo
    sunVisual->GetTransform()->scale = glm::vec3(0.00025f);
    AddGameObject(sunVisual);

    // Moon
    moon = new DirectionalLight();
    moon->SetTag("moon");
    moon->color = glm::vec3(0.4f, 0.5f, 0.8f);
    moon->intensity = 0.4f;
    AddGameObject(moon);

    // MoonVisual
    moonVisual = new ModelObject("../Assets/Modelos/Moon.obj", "../Assets/Texturas/Moon.png");
    moonVisual->SetUnlit(true);
    moonVisual->GetTransform()->scale = glm::vec3(3.0f);
    AddGameObject(moonVisual);

    // DayNightCycle
    dayNightCycle = new DayNightCycle(sun, moon);
    dayNightCycle->cycleDuration = 20.0f;
    dayNightCycle->orbitRadius = 70.0f; // Distancia a la escene
    
    dayNightCycle->onAmbientChanged = [this](glm::vec3 color, float intensity)
    {
        ambientColor = color;
        ambientIntensity = intensity;
    };
    AddGameObject(dayNightCycle);

    const short NUM_MODELS = 4;

    const std::string MODEL_PATHS[NUM_MODELS] =
    {
        "../Assets/Modelos/troll.obj",
        "../Assets/Modelos/rock.obj",
        "../Assets/Modelos/Primarina.obj",
        "../Assets/Modelos/TapuFini.obj",
    };
    const std::string TEXTURE_PATHS[NUM_MODELS] =
    {
        "../Assets/Texturas/troll.png",
        "../Assets/Texturas/rock.png",
        "../Assets/Texturas/Primarina.png",
        "../Assets/Texturas/TapuFini.png",
    };

    const glm::vec3 SPAWN_POINTS[] = 
    {
        glm::vec3(-7.0f, -0.8f,  -4.0f),
        glm::vec3(0.0f, -0.8f,  -4.0f),
        glm::vec3(7.0f, -0.8f,  -4.0f),
        glm::vec3(-4.0f, -0.8f,  -6.0f),
        glm::vec3(4.0f, -0.8f,  -6.0f),
        glm::vec3(-8.0f, -0.8f,  -7.0f),
        glm::vec3(-3.0f, -0.8f,  -8.0f),
        glm::vec3(0.0f, -0.8f,  -9.0f),
        glm::vec3(3.0f, -0.8f,  -8.0f),
        glm::vec3(8.0f, -0.8f,  -7.0f),
        glm::vec3(-8.0f, -0.8f, -10.0f),
        glm::vec3(-5.0f, -0.8f, -11.0f),
        glm::vec3(0.0f, -0.8f, -12.0f),
        glm::vec3(5.0f, -0.8f, -11.0f),
        glm::vec3(8.0f, -0.8f, -10.0f),
        glm::vec3(-8.0f, -0.8f, -12.0f),
        glm::vec3(-4.0f, -0.8f, -12.0f),
        glm::vec3(0.0f, -0.8f, -12.0f),
        glm::vec3(4.0f, -0.8f, -12.0f),
        glm::vec3(8.0f, -0.8f, -12.0f),
        glm::vec3(0.0f, -0.8f,  6.0f),
    };

    const short NUM_SPAWN_POINTS = 21;

    const float SCALE_MIN[NUM_MODELS] = { 0.25f, 0.25f, 0.003f, 0.003f};
    const float SCALE_MAX[NUM_MODELS] = { 0.35f, 0.40f, 0.004f, 0.004f};

    const float ROTX_MIN = -8.0f;
    const float ROTX_MAX = 8.0f;
    const float ROTY_MIN = 0.0f;
    const float ROTY_MAX = 360.0f;

    for (short i = 0; i < NUM_SPAWN_POINTS; i++)
    {
        //Elegir modelo aleatorio
        short modelIndex = rand() % NUM_MODELS;

        //Escala aleatoria
        float scale = RandomRange(SCALE_MIN[modelIndex], SCALE_MAX[modelIndex]);
        //Rotacion aleatoria
        float rotY = RandomRange(ROTY_MIN, ROTY_MAX);
        float rotX = RandomRange(-ROTX_MIN, ROTX_MAX);

        ModelObject* obj = new ModelObject(MODEL_PATHS[modelIndex], TEXTURE_PATHS[modelIndex]);

        obj->GetTransform()->position = SPAWN_POINTS[i];
        obj->GetTransform()->scale = glm::vec3(scale);
        obj->GetTransform()->rotation = glm::vec3(rotX, rotY, 0.0f);
        AddGameObject(obj);
    }

    const float FLOOR_Y = -1.2f;
    const float FLOOR_Z = -3.0f;
    const float FLOOR_SIZE_XZ = 20.0f;
    const float FLOOR_THICKNESS = 0.1f;

    //Suelo
    Cube* suelo = new Cube(
        glm::vec3(0.0f, FLOOR_Y, FLOOR_Z),
        glm::vec3(FLOOR_SIZE_XZ, FLOOR_THICKNESS, FLOOR_SIZE_XZ)
    );
    AddGameObject(suelo);

    // Sky
    glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
}

void MainScene::Update(float dt)
{
    Scene::Update(dt);

    // Luz y sol o luna en la misma pos
    if (sun && sunVisual)
    {
        sunVisual->GetTransform()->position = sun->GetTransform()->position;
    }

    if (moon && moonVisual)
    {
        moonVisual->GetTransform()->position = moon->GetTransform()->position;
    }

    // color del sky sigue cycle nightday
    glClearColor(ambientColor.r * 0.5f, ambientColor.g * 0.7f, ambientColor.b, 1.0f);
}