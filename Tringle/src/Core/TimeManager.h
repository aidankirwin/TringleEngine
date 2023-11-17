#pragma once

#include <string>
#include <map>
#include "Timer.h"
#include "Singleton.h"

class TimeManager : public Singleton<TimeManager>
{
public:
    ~TimeManager() {}

    void StartUp();
    void Update();
    void ShutDown();

    void AddTimer(Timer* timer, std::string SID);
    Timer* GetMainTimer();
private:

};