#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	mDeltaTime = 0;
	mLastFrame = static_cast<float>(glfwGetTime());
}

void Timer::Update()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	mDeltaTime = currentFrame - mLastFrame;
	mLastFrame = currentFrame;
}

void Timer::Stop()
{

}

float Timer::GetDelta()
{

}