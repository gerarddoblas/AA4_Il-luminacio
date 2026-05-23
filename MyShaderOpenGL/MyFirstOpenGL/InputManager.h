#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

#define IM InputManager::GetInstance()

enum KeyState { EMPTY, DOWN, UP, HOLD, RELEASED };

class InputManager
{
public:
	static InputManager* GetInstance()
	{
		static InputManager instance;
		return &instance;
	}

	void Init(GLFWwindow* newWindow);

	void Listen();

	double GetMouseX() const;
	double GetMouseY() const;
	bool GetKey(GLuint input, KeyState inputValue);

private:
	InputManager() = default;
	InputManager(InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	~InputManager() {}

	static void KeyBoardCallBack(GLFWwindow* newWindow, int key, int scancode, int action, int mods);
	static void MouseCallBack(GLFWwindow* newWindow, int button, int action, int mods);

	GLFWwindow* window = nullptr;

	//Son double porque glfwGetCursorPos() me obliga a pasar doubles, no hago cast por perdida de datos
	double mouseX = 0;
	double mouseY = 0;

	std::unordered_map<GLuint, KeyState> keyReference;
};