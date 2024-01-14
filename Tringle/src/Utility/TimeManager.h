#pragma once

#include <string>
#include <map>
#include "Timer.h"
#include "Singleton.h"

class TimeManager : public Singleton<TimeManager>
{
public:
    ~TimeManager() {}

    void Update();
    void ShutDown();

    Timer* AddTimer(std::string SID);
    Timer* GetTimer(std::string SID);
    void RemoveTimer(std::string SID);

    Timer* GetMainTimer();
    void SetMainTimer(std::string SID);

private:
    typedef std::map<std::string, Timer*> TimerMap;
    TimerMap* mTimers = new TimerMap();
    std::string mMainTimer;
};