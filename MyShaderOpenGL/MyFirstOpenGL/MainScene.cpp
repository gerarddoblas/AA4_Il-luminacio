#include "MainScene.h"
#include "Utils.h"

void MainScene::OnEnter()
{
    //Camera
    camera = new Camera();

    const std::string MODEL_PATHS[2] =
    {
        "../Assets/Modelos/troll.obj",
        "../Assets/Modelos/rock.obj",
    };
    const std::string TEXTURE_PATHS[2] =
    {
        "../Assets/Texturas/troll.png",
        "../Assets/Texturas/rock.png",
    };

    const glm::vec3 SPAWN_POINTS[] = 
    {
        glm::vec3(-6.0f,  -0.8f,  -5.0f),
        glm::vec3(0.0f,  -0.8f,  -6.0f),
        glm::vec3(6.0f,  -0.8f,  -5.0f),
        glm::vec3(-3.0f,  -0.8f,  -8.0f),
        glm::vec3(3.0f,  -0.8f,  -8.0f),
        glm::vec3(-10.0f, -0.8f, -12.0f),
        glm::vec3(-5.0f,  -0.8f, -13.0f),
        glm::vec3(0.0f,  -0.8f, -11.0f),
        glm::vec3(5.0f,  -0.8f, -14.0f),
        glm::vec3(10.0f, -0.8f, -12.0f),
        glm::vec3(-13.0f, -0.8f, -20.0f),
        glm::vec3(-8.0f,  -0.8f, -22.0f),
        glm::vec3(-2.0f,  -0.8f, -19.0f),
        glm::vec3(2.0f,  -0.8f, -21.0f),
        glm::vec3(8.0f,  -0.8f, -23.0f),
        glm::vec3(13.0f, -0.8f, -20.0f),
        glm::vec3(-14.0f, -0.8f, -30.0f),
        glm::vec3(-7.0f,  -0.8f, -32.0f),
        glm::vec3(0.0f,  -0.8f, -33.0f),
        glm::vec3(7.0f,  -0.8f, -31.0f),
        glm::vec3(14.0f, -0.8f, -30.0f),
    };

    const short NUM_SPAWN_POINTS = 21;

    const float SCALE_MIN[3] = { 0.25f, 0.25f, 0.20f };
    const float SCALE_MAX[3] = { 0.35f, 0.40f, 0.35f };

    for (short i = 0; i < NUM_SPAWN_POINTS; i++)
    {
        // Elegir modelo aleatorio
        short modelIndex = rand() % 2;

        // Escala aleatoria dentro del rango coherente del modelo
        float scale = RandomRange(SCALE_MIN[modelIndex], SCALE_MAX[modelIndex]);
        // Rotación aleatoria en Y (para que no parezcan todos iguales)
        float rotY = RandomRange(0.0f, 360.0f);
        float rotX = RandomRange(-8.0f, 8.0f);

        ModelObject* obj = new ModelObject(MODEL_PATHS[modelIndex], TEXTURE_PATHS[modelIndex]);
        obj->GetTransform()->position = SPAWN_POINTS[i];
        obj->GetTransform()->scale = glm::vec3(scale);
        obj->GetTransform()->rotation = glm::vec3(rotX, rotY, 0.0f);
        AddGameObject(obj);
    }

    //Suelo
    Cube* suelo = new Cube(
        glm::vec3(0.0f, -1.5f, -3.0f),
        glm::vec3(20.0f, 0.1f, 20.0f)
    );
    AddGameObject(suelo);

    //Cielo azul
    glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
}

void MainScene::Update(float dt)
{
    Scene::Update(dt);
}
