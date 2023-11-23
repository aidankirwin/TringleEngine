#include "TimeManager.h"

void TimeManager::Update()
{
    // Update all timers
    for (auto itr = mTimers->begin(); itr != mTimers->end(); ++itr)
    {
        auto iTimer = itr->second;
        iTimer->Update();
    }

    /*
    * Something to consider here is that currently all timers update approx. the same time.
    * It may be desirable to have specific timers that update during an activity.
    * E.g., a rendererTimer that updates only when the renderer updates.
    * TBD what the best way to do this is.
    * - Aidan
    */
}

void TimeManager::ShutDown()
{
    for (auto itr = mTimers->begin(); itr != mTimers->end(); ++itr)
    {
        auto iTimer = itr->second;
        delete iTimer;
    }

    mTimers->clear();
}

Timer* TimeManager::AddTimer(std::string SID)
{
    Timer* newTimer = new Timer();
    newTimer->Start();

    mTimers->insert(std::make_pair(SID, newTimer));

    return newTimer;
}

Timer* TimeManager::GetTimer(std::string SID)
{
    return mTimers->at(SID);
}

void TimeManager::RemoveTimer(std::string SID)
{
    Timer* t = mTimers->at(SID);
    t->Stop();

    mTimers->erase(SID);

    delete t;
}

Timer* TimeManager::GetMainTimer()
{
    return mTimers->at(mMainTimer);
}

void TimeManager::SetMainTimer(std::string SID)
{
    mMainTimer = SID;
}