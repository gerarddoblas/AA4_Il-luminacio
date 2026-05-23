#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "InputManager.h"
#include "Rendermanager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "Camera.h"

void main()
{
	srand(time(NULL));

	// Inicializamos GLFW
	glfwInit();

	// Inizializo el RenderManager
	RM->Init();

	// Inizializo el InputManager
	IM->Init(RM->GetWindow());


	SM.AddScene("Main", new MainScene());
	SM.InitFirstScene("Main");

	bool isRunning = true;

	// Generamos el game loop
	while (isRunning) {


		IM->Listen();

		TIME.Update();
			
		// Actualizamos el SceneManager
		SM.UpdateCurrentScene(TIME.GetDeltaTime());

		//RM->Update(TIME.GetDeltaTime());

		// Dibujado
		RM->ClearScreen();

		// El SceneManager renderiza
		if (SM.GetCurrentScene()) { SM.GetCurrentScene()->Render(); }

		RM->RenderScreen();

		if (glfwWindowShouldClose(RM->GetWindow()))
			isRunning = false;
	}

	RM->Release();
	glfwTerminate();
}