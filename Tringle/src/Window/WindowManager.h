#pragma once

#include <string>
#include <map>
#include "Window.h"
#include "Singleton.h"

// Currently multiple windows are supported. May want to remove
class WindowManager : public Singleton<WindowManager>
{
friend class Singleton<WindowManager>;
public:
    // Primary manager functions
    ~WindowManager();
    void StartUp();
    void Update();
    void ShutDown();

    void WindowPollEvents();
    
    // Window list functions
    void AddWindow(int width, int height, const char* title);
    void DeleteWindow(std::string windowName);
    Window* GetWindow(std::string windowName);

    // State enum and getter
    enum ManagerState
    {
        NOT_STARTED,
        STARTING_UP,
        POLLING_EVENTS,
        UPDATING,
        SHUTTING_DOWN
    };
    ManagerState GetState();

private:
    // All windows
    std::map<std::string, Window*>* mWindows = new std::map<std::string, Window*>();

    // Private state var
    ManagerState mState = ManagerState::NOT_STARTED;
};