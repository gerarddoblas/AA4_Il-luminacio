#include "InputManager.h"
#include <iostream>

void InputManager::Init(GLFWwindow* newWindow)
{
    window = newWindow;

    glfwSetKeyCallback(window, KeyBoardCallBack);
    glfwSetMouseButtonCallback(window, MouseCallBack);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
}

void InputManager::Listen()
{
    for (std::unordered_map<GLuint, KeyState>::iterator it = keyReference.begin(); it != keyReference.end(); it++)
    {
        if (it->second == DOWN)
            it->second = HOLD;
        if (it->second == UP)
            it->second = RELEASED;
    }

    prevMouseX = mouseX;
    prevMouseY = mouseY;

    glfwGetCursorPos(window, &mouseX, &mouseY);

    if(firstMouseRead)
    {
        prevMouseX = mouseX;
        prevMouseY = mouseY;
        firstMouseRead = false;
    }

    glfwPollEvents();
}

double InputManager::GetMouseX() const { return mouseX; }

double InputManager::GetMouseY() const { return mouseY; }

double InputManager::GetMouseDeltaX() const { return mouseX - prevMouseX; }
double InputManager::GetMouseDeltaY() const { return mouseY - prevMouseY; }

bool InputManager::GetKey(GLuint input, KeyState inputValue) { return keyReference[input] == inputValue; }

void InputManager::KeyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //Compruebo si la 'action' de la 'key' del teclado está presionada o soltada
    if (action == GLFW_PRESS)
        IM->keyReference[key] = DOWN;
    else if (action == GLFW_RELEASE)
        IM->keyReference[key] = UP;
}

void InputManager::MouseCallBack(GLFWwindow* window, int button, int action, int mods)
{
    //Compruebo si la 'action' del ratón está presionada o soltada
    if(action == GLFW_PRESS)
        IM->keyReference[button] = DOWN;
    else if (action == GLFW_RELEASE)
        IM->keyReference[button] = UP;
}