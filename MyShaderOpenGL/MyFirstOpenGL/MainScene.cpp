#include "MainScene.h"

void MainScene::OnEnter()
{
    //Camera
    camera = new Camera();

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
    troll4->GetTransform()->rotation = glm::vec3(0.0f,0.0f, 0.0f);
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
    if (IM->GetKey(GLFW_KEY_1, DOWN))
    {
        camera->SetTarget(FindByTag("troll2"));
        camera->SetPositionFromTarget(glm::vec3(0.0f, 2.0f, 3.0f));
        camera->SetMode(CameraMode::STATIC);
    }

    if (IM->GetKey(GLFW_KEY_2, DOWN))
    {
        camera->SetTarget(FindByTag("troll3"));
        camera->SetPositionFromTarget(glm::vec3(0.0f, 1.0f, 0.7f));
        camera->SetMode(CameraMode::STATIC);

    }

    if (IM->GetKey(GLFW_KEY_3, DOWN))
    {
        camera->SetTarget(FindByTag("troll4"));
        camera->SetPositionFromTarget(glm::vec3(0.0f, 1.5f, 5.0f));
        camera->SetMode(CameraMode::DOLLYZOOM);
    }

    Scene::Update(dt);
}
