#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

Timer::Start()
{
	mDeltaTime = 0;
	mLastFrame = static_cast<float>(glfwGetTime());
}

Timer::Update()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	mDeltaTime = currentFrame - mLastFrame;
	mLastFrame = currentFrame;
}