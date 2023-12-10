#pragma once

#include "Application.h"
#include "RenderManager.h"
#include "Window.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Singleton.h"
#include "EventManager.h"
#include "Camera.h"

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

        // Bin directory path variable
        // Only had path issues when testing on mac
        // But nice to have
        std::string BIN_PATH;
        void SetPath(char *argv[])
        {
            std::string path;
            size_t end;

            // Get path
            for(int i = 0; argv[i] !=0; i++)
            {
                path += argv[i];
            }

            // Remove program name
            // Slash direction is OS dependent
            #ifdef _WIN32
            end = path.rfind("\\");
            if(end != std::string::npos)
            {
                path.replace(end, 100, "\\");
            }
            #endif

            #ifdef __APPLE__
            end = path.rfind("/");
            if (end != std::string::npos)
            {
                path.replace(end, 100, "/");
            }
            #endif

            // Print for testing
            // Should start storing print calls somewhere
            std::cout << path << '\n';

            BIN_PATH = path;
        }

    private:
        Window* mWindow;

        // Subsystem manager singletons
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