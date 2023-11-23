#pragma once

#include <glad.h>
#include <glfw3.h>

class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Update();
	void Stop();

	float GetDelta();

private:
	float mDeltaTime;
	float mLastFrame;
};