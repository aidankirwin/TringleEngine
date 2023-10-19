#pragma once
#include "Timer.h"
#include "Singleton.h"
#include "Core.h"
#include <string>

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