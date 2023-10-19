#pragma once

#include "Application.h"
#include "RenderManager.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Singleton.h"
#include "Core.h"
#include "EventManager.h"

namespace Tringle
{
    class Application
    {
    public:
        Application()
        {
            mInstance = this;
        }
        ~Application() {}

        // Subsystem management and main while loop
        void Run();

        // Inheritable virtual app functions
        virtual void StartUp() {}
        virtual void Update() {}
        virtual void ShutDown() {}

        static Application* GetApplication()
        {
            return mInstance;
        }

        static void Quit()
        {
            mRunning = false;
        }

    private:
        // Subsystem manager singletons
        WindowManager mWindowManager;
        RenderManager mRenderManager;
        SceneManager   mSceneManager;
        TimeManager     mTimeManager;
        
        // Single instance
        // It would be nice to make Application a child of Singleton,
        // or make an additional Singleton base class for dynamically allocated singletons like this
        // but this works for now
        static Application* mInstance;

        static bool mRunning;
    };

    // Defined by user 
    // Called by Tringle in EntryPoint
    Application* CreateApplication();
}