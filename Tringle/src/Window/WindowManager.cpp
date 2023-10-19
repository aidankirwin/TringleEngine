#include "WindowManager.h"

WindowManager::~WindowManager()
{
}

void WindowManager::StartUp()
{
    mState = ManagerState::STARTING_UP;

    for (auto itr = mWindows->begin(); itr != mWindows->end(); ++itr)
    {
        auto iWindow = itr->second;
        iWindow->StartUp();
    }
}

void WindowManager::Update()
{
    mState = ManagerState::UPDATING;

    for (auto itr = mWindows->begin(); itr != mWindows->end(); ++itr)
    {
        auto iWindow = itr->second;
        iWindow->Update();
    }
}

void WindowManager::ShutDown()
{
    mState = ManagerState::SHUTTING_DOWN;

    for (auto itr = mWindows->begin(); itr != mWindows->end(); ++itr)
    {
        auto iWindow = itr->second;
        iWindow->ShutDown();
    }
}

void WindowManager::WindowPollEvents()
{
    for (auto itr = mWindows->begin(); itr != mWindows->end(); ++itr)
    {
        auto iWindow = itr->second;
        iWindow->PollEvents();
    }
}

WindowManager::ManagerState WindowManager::GetState()
{
    return mState;
}

void WindowManager::AddWindow(int width, int height, const char* title)
{
    Window* newWindow = new Window(width, height, title);

    // Need to call StartUp on Windows added after WindowManager start up
    if (mState == ManagerState::UPDATING)
    {
        newWindow->StartUp();
    }

    // NOTE: this assumes no two windows share the same name
    // May need to fix this eventually

    mWindows->insert(std::make_pair(title, newWindow));
}

void WindowManager::DeleteWindow(std::string windowName)
{
    auto iWindow = mWindows->at(windowName);
    iWindow->ShutDown();
    mWindows->erase(windowName);
}

Window* WindowManager::GetWindow(std::string windowName)
{
    return mWindows->at(windowName);
}