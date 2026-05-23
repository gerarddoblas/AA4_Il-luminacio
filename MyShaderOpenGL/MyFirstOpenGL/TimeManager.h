#pragma once

#include <cmath>
#include <GLFW/glfw3.h>

#define TIME TimeManager::Instance()

class TimeManager
{
private:
	TimeManager();
	~TimeManager() = default;

	TimeManager(const TimeManager& t) = delete;
	TimeManager& operator = (const TimeManager& t) = delete;

	//Time control
	float deltaTime;
	float elapsedTime;
	float previousElapsedTime;

	//FPS control
	const int FPS = 60;
	float frameTime;


	float timeMultiplier = 1.0f;

public:
	static TimeManager& Instance()
	{
		static TimeManager instance;

		return instance;
	}

	float GetDeltaTime();
	void SetTimeMultiplier(float m);
	float GetTimeMultiplier() const;
	float GetElapsedTime();
	float GetFrameTime();

	bool ShouldUpdateGame();

	void Update();
};