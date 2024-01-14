#include "Timer.h"

Timer::Timer() : mDeltaTime(0), mLastFrame(0), mRunning(true)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	mLastFrame = static_cast<float>(glfwGetTime());
}

void Timer::Update()
{
	if (!mRunning) return;
	float currentFrame = static_cast<float>(glfwGetTime());
	mDeltaTime = currentFrame - mLastFrame;
	mLastFrame = currentFrame;
}

void Timer::Stop()
{
	mRunning = false;
}

float Timer::GetDelta()
{
	return mDeltaTime;
}