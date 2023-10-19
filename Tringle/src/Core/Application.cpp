#include "Application.h"

namespace Tringle
{
    Application* Application::mInstance = NULL;
    bool Application::mRunning = true;

    void Application::Run()
    {
        // Get manager singletons
        mWindowManager = Singleton<WindowManager>::GetInstance();
        mSceneManager = Singleton<SceneManager>::GetInstance(); // TODO
        mTimeManager = Singleton<TimeManager>::GetInstance(); // TODO
        mRenderManager = Singleton<RenderManager>::GetInstance();

        StartUp();                              // User defined app start up

        // Start up engine systems in the correct order
        mWindowManager.StartUp();
        mRenderManager.StartUp();

        // Main game loop.
        while (mRunning)
        {
            mWindowManager.WindowPollEvents();  // Poll events
            mTimeManager.Update();              // Update active timers

            Update();                           // User defined app update

            // Update engine systems in order
            mRenderManager.Update();            // Update active renderables
            mWindowManager.Update();            // Swap buffers
        }

        ShutDown();                             // User defined app shut down

        // Shut down engine systems in the reverse order
        mRenderManager.ShutDown();
        mWindowManager.ShutDown();
    }
}