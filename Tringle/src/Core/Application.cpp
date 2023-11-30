#include "Application.h"

namespace Tringle
{
    Application* Application::mInstance = NULL;
    bool Application::mRunning = true;

    void Application::Run()
    {
        // Get manager singletons
        mSceneManager = Singleton<SceneManager>::GetInstance(); // TODO
        mTimeManager = Singleton<TimeManager>::GetInstance();
        mRenderManager = Singleton<RenderManager>::GetInstance();

        StartUp();                              // User defined app start up

        // Start up engine systems in the correct order
        mRenderManager.StartUp();
        mTimeManager.AddTimer("DEFAULT");
        mTimeManager.SetMainTimer("DEFAULT");

        // Create window
        mWindow = new Window(800, 600, "test");
        mWindow->StartUp();

        Shader shaderTest("default.vs", "default.fs");

        // Main game loop.
        while (mRunning)
        {
            // Window handling
            mWindow->PollEvents();               // Poll events

            // Update engine systems in order
            mTimeManager.Update();              // Update active timers
            
            Update();                           // User defined app update
            
            mRenderManager.Update();            // Update active renderables

            // More window handling
            mWindow->SwapBuffers();             // Swap buffers
        }

        // Close window
        mWindow->ShutDown();

        ShutDown();                             // User defined app shut down

        // Shut down engine systems in the reverse order
        mRenderManager.ShutDown();
        mTimeManager.ShutDown();
    }
}