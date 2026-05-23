#include "TimeManager.h"

TimeManager::TimeManager()
{
	deltaTime = 0.0f;
	elapsedTime = glfwGetTime();
	previousElapsedTime = 0.0f;

	frameTime = 1.0f / (float)FPS;
}

float TimeManager::GetDeltaTime() { return deltaTime; }

void TimeManager::SetTimeMultiplier(float m) { timeMultiplier = m; }

float TimeManager::GetTimeMultiplier() const { return timeMultiplier; }

float TimeManager::GetElapsedTime() { return elapsedTime; }

float TimeManager::GetFrameTime() { return frameTime; }

bool TimeManager::ShouldUpdateGame() { return deltaTime >= frameTime; }

void TimeManager::Update()
{
	elapsedTime = (float)glfwGetTime();
	deltaTime = (elapsedTime - previousElapsedTime) * timeMultiplier;
	previousElapsedTime = elapsedTime;
}
