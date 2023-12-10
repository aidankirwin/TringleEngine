#include "Application.h"

namespace Tringle
{
    Application* Application::mInstance = NULL;
    bool Application::mRunning = true;

    void Application::Run()
    {
        Log::DebugMsg("Path to bin dir: " + BIN_PATH);
        Log::DebugMsg("======= START UP =======");

        // Get manager singletons
        mSceneManager = Singleton<SceneManager>::GetInstance(); // TODO
        mTimeManager = Singleton<TimeManager>::GetInstance();
        mRenderManager = Singleton<RenderManager>::GetInstance();

        StartUp();                                  // User defined app start up

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

        Log::DebugMsg("Create shader");
        Shader shader;
        shader.Create(BIN_PATH + "default.vert", BIN_PATH + "default.frag");
        Error::GLError();
        Log::DebugMsg("Use shader");
        shader.Use();
        Error::GLError();

        Log::DebugMsg("Set view and projection matrix uniforms");
        shader.SetMat4("view", view);
        shader.SetMat4("projection", proj);
        Error::GLError();

                      // Position data             // Texture data
        Vertex v1 = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) }; // 0
        Vertex v2 = { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) }; // 1
        Vertex v3 = { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) }; // 2
        Vertex v4 = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) }; // 3

        std::vector<Vertex> vert = { v1, v2, v3, v4 };
        std::vector<unsigned int> indices = { 0,  1,  3,  3,  1,  2 };

        Log::DebugMsg("Load texture");
        Texture texTest;
        texTest.Create(BIN_PATH + "tex.jpg");
        Error::GLError();

        Transform test;
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, -20.0f);
        glm::vec3 scale = glm::vec3(5, 5, 1);
        float angle = 0.0f;
        glm::vec3 axis = glm::vec3(0, 0, 1);
        test.Position = pos;
        test.Scale = scale;
        test.Rotation = { axis, angle };

        Mesh meshTest(vert, indices);

        meshTest.Initialize();

        Log::DebugMsg("======= UPDATE BEGIN =======");

        // Main game loop.
        while (mRunning)
        {
            // Window handling
            mWindow->StartRender();                 // Clear

            // Update engine systems in order
            mTimeManager.Update();
            
            Update();                               // User defined app update
            
            shader.Use();
            texTest.Use();
            // mRenderManager.Update();
            meshTest.Draw(shader, texTest, test);

            // More window handling
            mWindow->SwapBuffersAndPollEvents();    // Swap buffers
        }

        // Close window
        mWindow->ShutDown();

        ShutDown();                                 // User defined app shut down

        // Shut down engine systems in the reverse order
        mRenderManager.ShutDown();
        mTimeManager.ShutDown();
    }
}