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
        // Create window
        mWindow = new Window(800, 600, "test");
        mWindow->StartUp();

        mRenderManager.StartUp();
        mTimeManager.AddTimer("DEFAULT");
        mTimeManager.SetMainTimer("DEFAULT");

        Camera camTest(800, 600);

        glm::mat4 proj = camTest.GetProjectionMatrix();
        glm::mat4 view = camTest.GetViewMatrix();

        mShader = new Shader();
        std::cout << "test: " << BIN_PATH << '\n';
        mShader->LoadFromFiles(BIN_PATH + "default.vert", BIN_PATH + "default.frag");

        // Make sure to call shader.Use before doing this
        //shaderTest.SetMat4("view", view);
        //shaderTest.SetMat4("projection", proj);

        Vertex v1 = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
        Vertex v2 = { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
        Vertex v3 = { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
        Vertex v4 = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) };

        std::vector<Vertex> vert = { v1, v2, v3, v4 };
        std::vector<unsigned int> indices = { 0,  1,  3,  3,  1,  2 };

        //Texture texTest;
        //texTest.LoadFromFiles("tex.jpg");
        //shaderTest.SetInt("sprite", 0);

        Mesh meshTest(vert, indices);

        meshTest.Initialize();

        // Main game loop.
        while (mRunning)
        {
            // Window handling
            mWindow->StartRender();               // Clear

            // Update engine systems in order
            mTimeManager.Update();              // Update active timers
            
            Update();                           // User defined app update
            
            mShader->Use();

            // mRenderManager.Update();            // Update active renderables
            meshTest.Draw();

            // More window handling
            mWindow->SwapBuffersAndPollEvents();             // Swap buffers
        }

        // Close window
        mWindow->ShutDown();

        ShutDown();                             // User defined app shut down

        // Shut down engine systems in the reverse order
        mRenderManager.ShutDown();
        mTimeManager.ShutDown();
    }
}